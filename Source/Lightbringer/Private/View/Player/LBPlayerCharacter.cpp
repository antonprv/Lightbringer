// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerCharacter.h"
#include "PlayerDelegateMediator.h"
#include "ComponentsDelegateMediator.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

#include "Components/LBCharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/FakeShadowComponent.h"

#include "Components/TextRenderComponent.h"

#include "TimerManager.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogALBPlayerCharacter, Log, Log)

/*
 * Class constructor
 */
ALBPlayerCharacter::ALBPlayerCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<ULBCharacterMovementComponent>(
          ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    SpringArmComponent =
        CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->CameraLagSpeed = 25.f;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->bUsePawnControlRotation = true;

    SpringArmComponent->SocketOffset = {144.f, 78.f, 66.f};

    DefaultSocketRightOffset = SpringArmComponent->SocketOffset.Y;
    CurrentSocketRightOffset = DefaultSocketRightOffset;

    DefaultSprintRightCameraInterpolationSpeed =
        SprintRightCameraInterpolationSpeed;

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

    TextRenderComponent->bOwnerNoSee = true;

    FakeShadowComponent =
        CreateDefaultSubobject<UFakeShadowComponent>("Fake Shadow");
    FakeShadowComponent->SetupAttachment(GetRootComponent());

    WeaponComponent =
        CreateDefaultSubobject<UWeaponComponent>("Weapon Component");

    AnimationComponent =
        CreateDefaultSubobject<UAnimationComponent>("Animation Component");
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

    ComponentsDelegateMediator = UComponentsDelegateMediator::Get(GetWorld());
    MovementHandlerComponent =
        Cast<ULBCharacterMovementComponent>(GetCharacterMovement());

    check(MovementHandlerComponent);
    check(ComponentsDelegateMediator);

    OnHealthChanged(HealthComponent->GetHealth());

    if (!ComponentsDelegateMediator->OnActorDeath.IsBoundToObject(this))
    {
        ComponentsDelegateMediator->OnActorDeath.AddUObject(
            this, &ALBPlayerCharacter::HandleActorDeath);
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

void ALBPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FRotator DesiredRotation = {
        -GetWorld()->GetFirstPlayerController()->GetControlRotation().Pitch,
        GetWorld()->GetFirstPlayerController()->GetControlRotation().Yaw +
            180.f,
        0.f};

    TextRenderComponent->SetWorldRotation(DesiredRotation);

    InterpolateSprintCamera(DeltaSeconds);
    InterpolateSprintRightCamera(DeltaSeconds);
}

void ALBPlayerCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    HealthComponent->OnHealthChanged.RemoveAll(this);
    LandedDelegate.RemoveAll(this);

    Super::EndPlay(EndPlayReason);
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

void ALBPlayerCharacter::HandleActorDeath(AActor* DeadActor)
{
    if (!GetWorld() || DeadActor != this) return;

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->DisableMovement();

    if (UPlayerDelegateMediator* DelegateMediator =
            UPlayerDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerDeath(this);
    }
}

void ALBPlayerCharacter::OnGroundLanding(const FHitResult& Hit)
{
    if (!GetWorld()) return;

    MovementHandlerComponent->SetLandingRules();

    float JumpVelocity = -GetCharacterMovement()->Velocity.Z;

    if (ComponentsDelegateMediator)
    {
        ComponentsDelegateMediator->DispatchPlayerJumpDamage(
            this, JumpVelocity, Hit);
    }

    UE_LOG(LogALBPlayerCharacter, Display,
        TEXT("Jump velocity on landing: %f"), JumpVelocity);
}

/*
 * Pure view functions
 */
void ALBPlayerCharacter::InterpolateSprintCamera(const float& DeltaSeconds)
{
    if (!GetWorld()) return;

    const float TargetFOV = MovementHandlerComponent->IsSprinting()
                                ? SprintCameraFOV
                                : DefaultCameraFOV;

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

void ALBPlayerCharacter::InterpolateSprintRightCamera(
    const float& DeltaSeconds)
{
    if (!GetWorld()) return;

    const float TargetOffset = MovementHandlerComponent->bIsMovingRight &&
                                       MovementHandlerComponent->IsSprinting()
                                   ? -DefaultSocketRightOffset
                                   : DefaultSocketRightOffset;

    if (FMath::IsNearlyEqual(
            CurrentSocketRightOffset, TargetOffset, KINDA_SMALL_NUMBER))
    {
        if (SpringArmComponent->SocketOffset.Y != TargetOffset)
        {
            SpringArmComponent->SocketOffset.Y = TargetOffset;
        }

        return;
    }

    SprintRightCameraInterpolationSpeed =
        MovementHandlerComponent->IsSprinting()
            ? DefaultSprintRightCameraInterpolationSpeed
            : SprintCameraInterpolationSpeed;

    CurrentSocketRightOffset = FMath::FInterpTo(CurrentSocketRightOffset,
        TargetOffset, DeltaSeconds, SprintRightCameraInterpolationSpeed);

    SpringArmComponent->SocketOffset.Y = CurrentSocketRightOffset;
}

void ALBPlayerCharacter::DisplayText(const float& CurrentHealth)
{
    if (!TextRenderComponent) return;

    TextRenderComponent->SetText(
        FText::FromString(FString::Printf(TEXT("%.0f"), CurrentHealth)));
}

/*
 * Interfaces
 */
void ALBPlayerCharacter::MoveForwardCustom_Implementation(const float& Value)
{
    if (!MovementHandlerComponent) return;

    MovementHandlerComponent->SetForwardInput(Value);
}

void ALBPlayerCharacter::MoveRightCustom_Implementation(const float& Value)
{
    if (!MovementHandlerComponent) return;

    MovementHandlerComponent->SetRightInput(Value);
}

void ALBPlayerCharacter::LookUpCustom_Implementation(const float& Value)
{
    if (!MovementHandlerComponent) return;

    MovementHandlerComponent->SetLookUpInput(Value);
}

void ALBPlayerCharacter::TurnAroundCustom_Implementation(const float& Value)
{
    if (!MovementHandlerComponent) return;

    MovementHandlerComponent->SetTurnAroundInput(Value);
}

void ALBPlayerCharacter::JumpCustom_Implementation()
{
    if (!MovementHandlerComponent) return;

    MovementHandlerComponent->PerformJump();
}

void ALBPlayerCharacter::StartSprinting_Implementation()
{
    if (!MovementHandlerComponent) return;

    MovementHandlerComponent->SetStartSprinting();
}

void ALBPlayerCharacter::StopSprinting_Implementation()
{
    if (!MovementHandlerComponent) return;

    MovementHandlerComponent->SetStopSprinting();
}
