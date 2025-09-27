// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerCharacter.h"
#include "PlayerDelegateMediator.h"
#include "ComponentsDelegateMediator.h"

#include "LBWeaponBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Components/LBCharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "Animation/AnimMontage.h"

DEFINE_LOG_CATEGORY_STATIC(LogALBPlayerCharacter, Log, Log)

/*
 * Class constructor
 */
ALBPlayerCharacter::ALBPlayerCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<ULBCharacterMovementComponent>(
          ACharacter::CharacterMovementComponentName))
{
    MovementHandlerComponent =
        Cast<ULBCharacterMovementComponent>(GetCharacterMovement());

    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->AirControl = 0.2f;

    SpringArmComponent =
        CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->CameraLagSpeed = 25.f;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent =
        CreateDefaultSubobject<UCameraComponent>("Player Camera");
    CameraComponent->SetupAttachment(
        SpringArmComponent, USpringArmComponent::SocketName);
    CameraComponent->bUsePawnControlRotation = false;

    DefaultCameraFOV = CameraComponent->FieldOfView;
    CurrentCameraFOV = DefaultCameraFOV;

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

    SpawnWeapon();
}

void ALBPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    InterpolateCamera(DeltaSeconds);
}

void ALBPlayerCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    HealthComponent->OnDeath.RemoveAll(this);
    HealthComponent->OnHealthChanged.RemoveAll(this);
    LandedDelegate.RemoveAll(this);

    Super::EndPlay(EndPlayReason);
}

/*
 * Animation parameters
 */
void ALBPlayerCharacter::SpawnWeapon()
{
    if (!GetWorld()) return;

    WeaponMesh = GetWorld()->SpawnActor<ALBWeaponBase>(WeaponClass);
    if (WeaponMesh)
    {
        FAttachmentTransformRules AttachmentRules(
            EAttachmentRule::SnapToTarget, false);
        WeaponMesh->AttachToComponent(
            GetMesh(), AttachmentRules, FName("WeaponSocket"));
    }
}

void ALBPlayerCharacter::UpdateLeftHandRotation()
{
    if (!WeaponMesh) return;

    WeaponLeftHandSocketRotation =
        WeaponMesh->SkeletalMesh->GetSocketRotation(FName("LeftHandSocket"));
}

void ALBPlayerCharacter::UpdateLeftHandLocation()
{
    if (!WeaponMesh) return;

    WeaponLeftHandSocketLocation =
        WeaponMesh->SkeletalMesh->GetSocketLocation(FName("LeftHandSocket"));
}

/*
 * Player Movement
 */
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

    MovementHandlerComponent->SetIsJumpAllowed(false);

    float JumpVelocity = -GetCharacterMovement()->Velocity.Z;

    if (UComponentsDelegateMediator* DelegateMediator =
            UComponentsDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerJumpDamage(JumpVelocity, Hit);
    }

    UE_LOG(LogALBPlayerCharacter, Display,
        TEXT("Jump velocity on landing: %f"), JumpVelocity);

    GetWorldTimerManager().SetTimer(JumpHandle, this,
        &ALBPlayerCharacter::AllowJumping, 0.01f, false, JumpDelay);
}

void ALBPlayerCharacter::AllowJumping()
{
    MovementHandlerComponent->SetIsJumpAllowed(true);

    JumpHandle.Invalidate();
}

/*
 * Pure view functions
 */
void ALBPlayerCharacter::InterpolateCamera(const float& DeltaSeconds)
{
    if (!GetWorld()) return;

    const float TargetFOV = MovementHandlerComponent->IsSprinting() || bIsDying
                                ? SprintCameraFOV
                                : DefaultCameraFOV;

    // If already close enough, just set FOV once and return
    if (FMath::IsNearlyEqual(CurrentCameraFOV, TargetFOV, KINDA_SMALL_NUMBER))
    {
        if (CameraComponent->FieldOfView != TargetFOV)
        {
            CameraComponent->SetFieldOfView(TargetFOV);
        }

        return;
    }

    CurrentCameraFOV = FMath::FInterpTo(CurrentCameraFOV, TargetFOV,
        DeltaSeconds, SprintCameraInterpolationSpeed);

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
    MovementHandlerComponent->SetForwardInput(Value);
}

void ALBPlayerCharacter::MoveRightCustom_Implementation(const float& Value)
{
    MovementHandlerComponent->SetRightInput(Value);
}

void ALBPlayerCharacter::LookUpCustom_Implementation(const float& Value)
{
    MovementHandlerComponent->SetLookUpInput(Value);
}

void ALBPlayerCharacter::TurnAroundCustom_Implementation(const float& Value)
{
    MovementHandlerComponent->SetTurnAroundInput(Value);
}

void ALBPlayerCharacter::JumpCustom_Implementation()
{
    MovementHandlerComponent->PerformJump();
}

void ALBPlayerCharacter::StartSprinting_Implementation()
{
    MovementHandlerComponent->SetStartSprinting();
}

void ALBPlayerCharacter::StopSprinting_Implementation()
{
    MovementHandlerComponent->SetStopSprinting();
}
