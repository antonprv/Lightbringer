// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerCharacter.h"
#include "PlayerDelegateMediator.h"
#include "ComponentsDelegateMediator.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "Animation/AnimMontage.h"

DEFINE_LOG_CATEGORY_STATIC(LogALBPlayerCharacter, Log, Log)

/*
 * Class constructor
 */
ALBPlayerCharacter::ALBPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent =
        CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->CameraLagSpeed = 25.f;
    SpringArmComponent->bEnableCameraLag = true;

    CameraComponent =
        CreateDefaultSubobject<UCameraComponent>("Player Camera");
    CameraComponent->SetupAttachment(SpringArmComponent);

    DefaultCameraFOV = CameraComponent->FieldOfView;
    CurrentCameraFOV = DefaultCameraFOV;
    DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

    HealthComponent =
        CreateDefaultSubobject<UHealthComponent>("Health Component");
    TextRenderComponent =
        CreateDefaultSubobject<UTextRenderComponent>("Health Text");
    TextRenderComponent->SetupAttachment(GetRootComponent());
}

/*
 * Setup default values and do checks
 */
void ALBPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(TextRenderComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());

    if (!HealthComponent->OnDeath.IsBoundToObject(this))
    {
        HealthComponent->OnDeath.AddUObject(
            this, &ALBPlayerCharacter::OnDeath);
    }

    if (!HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(
            this, &ALBPlayerCharacter::OnHealthChanged);
    }

    if (!LandedDelegate.Contains(this,
            GET_FUNCTION_NAME_CHECKED(ALBPlayerCharacter, OnGroundLanding)))
    {
        LandedDelegate.AddDynamic(this, &ALBPlayerCharacter::OnGroundLanding);
    }

    if (!LandedDelegate.Contains(this,
            GET_FUNCTION_NAME_CHECKED(ALBPlayerCharacter, HandleDestruction)))
    {
        OnDestroyed.AddDynamic(this, &ALBPlayerCharacter::HandleDestruction);
    }
}

void ALBPlayerCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    HealthComponent->OnDeath.RemoveAll(this);
    HealthComponent->OnHealthChanged.RemoveAll(this);
    LandedDelegate.RemoveAll(this);

    Super::EndPlay(EndPlayReason);
}

void ALBPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    InterpolateCamera(DeltaTime);
}

void ALBPlayerCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*
 * Player Movement
 */
bool ALBPlayerCharacter::IsSprinting()
{
    return bIsMovingForward && bWantsToSprint && !GetVelocity().IsZero();
}

void ALBPlayerCharacter::Jump()
{
    Super::Jump();
}

/*
 * Callback functions
 */
void ALBPlayerCharacter::HandleDestruction(AActor* DestroyedActor)
{
    if (UPlayerDelegateMediator* DelegateMediator =
            UPlayerDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerDestruction(DestroyedActor);
    }
}

void ALBPlayerCharacter::OnHealthChanged(float CurrentHealth)
{
    DisplayText(CurrentHealth);
}

void ALBPlayerCharacter::OnDeath()
{
    if (!GetWorld()) return;

    bIsDying = true;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->DisableMovement();
    PlayAnimMontage(DeathMontage);

    if (UPlayerDelegateMediator* DelegateMediator =
            UPlayerDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerDeath(this);
    }
}

void ALBPlayerCharacter::OnGroundLanding(const FHitResult& Hit)
{
    if (!GetWorld()) return;

    float JumpVelocity = -GetCharacterMovement()->Velocity.Z;

    if (UComponentsDelegateMediator* DelegateMediator =
            UComponentsDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerJumpDamage(JumpVelocity, Hit);
    }

    UE_LOG(LogALBPlayerCharacter, Display,
        TEXT("Jump velocity on landing: %f"), JumpVelocity);
}

/*
 * Pure view functions
 */
void ALBPlayerCharacter::InterpolateCamera(const float& DeltaTime)
{
    const float TargetFOV =
        IsSprinting() || bIsDying ? SprintCameraFOV : DefaultCameraFOV;

    // If already close enough, just set FOV once and return
    if (FMath::IsNearlyEqual(CurrentCameraFOV, TargetFOV, KINDA_SMALL_NUMBER))
    {
        if (CameraComponent->FieldOfView != TargetFOV)
        {
            CameraComponent->SetFieldOfView(TargetFOV);
        }
        return;
    }

    CurrentCameraFOV = FMath::FInterpTo(
        CurrentCameraFOV, TargetFOV, DeltaTime, SprintCameraInterpolation);

    CameraComponent->SetFieldOfView(CurrentCameraFOV);
}

void ALBPlayerCharacter::DisplayText(const float& CurrentHealth)
{
    TextRenderComponent->SetText(
        FText::FromString(FString::Printf(TEXT("%.0f"), CurrentHealth)));
}

/*
 * Interfaces
 */
void ALBPlayerCharacter::MoveForwardCustom_Implementation(const float& Value)
{
    bIsMovingForward = Value > 0;
    AddMovementInput(GetActorForwardVector(), Value);
}

void ALBPlayerCharacter::MoveRightCustom_Implementation(const float& Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ALBPlayerCharacter::LookUpCustom_Implementation(const float& Value)
{
    AddControllerPitchInput(Value);
}

void ALBPlayerCharacter::TurnAroundCustom_Implementation(const float& Value)
{
    AddControllerYawInput(Value);
}

void ALBPlayerCharacter::JumpCustom_Implementation()
{
    Jump();
}

void ALBPlayerCharacter::StartSprinting_Implementation()
{
    if (!GetCharacterMovement()->IsMovingOnGround()) return;

    bWantsToSprint = true;
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ALBPlayerCharacter::StopSprinting_Implementation()
{
    bWantsToSprint = false;
    GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}