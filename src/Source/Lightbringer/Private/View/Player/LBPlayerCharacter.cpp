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
#include "GameFramework/PlayerController.h"

#include "Components/LBCharacterMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/FakeShadowComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"

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
    // Setup default C++ API parameters
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    SpringArmComponent =
        CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->bEnableCameraLag = true;
    SpringArmComponent->CameraLagSpeed = 2.5f;
    SpringArmComponent->CameraLagMaxDistance = 45.f;
    SpringArmComponent->bUsePawnControlRotation = true;

    SpringArmComponent->SocketOffset = {144.f, 78.f, 66.f};

    DefaultSocketRightOffset = SpringArmComponent->SocketOffset.Y;
    CurrentSocketRightOffset = DefaultSocketRightOffset;

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

    WeaponComponent =
        CreateDefaultSubobject<UWeaponComponent>("Weapon Component");

    AnimationComponent =
        CreateDefaultSubobject<UAnimationComponent>("Animation Component");

    // Set default values
    SprintCameraFOV = 100.f;
    SlideCameraFOV = 120.f;
    JumpCameraFOV = 120.f;
    SprintCameraInterpolationSpeed = 5.f;
    SprintRightCameraInterpolationSpeed = 0.8f;
    DefaultSprintRightCameraInterpolationSpeed =
        SprintRightCameraInterpolationSpeed;
}

/*
 * Setup default values and perform checks
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

    BindDelegates();
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

    InterpolateCamera(DeltaSeconds);
    InterpolateSprintRightCamera(DeltaSeconds);
}

void ALBPlayerCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    HealthComponent->OnHealthChanged.RemoveAll(this);
    LandedDelegate.RemoveAll(this);

    Super::EndPlay(EndPlayReason);
}

void ALBPlayerCharacter::BindDelegates()
{
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
void ALBPlayerCharacter::InterpolateCamera(const float& DeltaSeconds)
{
    if (!GetWorld()) return;

    float TargetFOV;

    if (MovementHandlerComponent->IsSprinting())
    {
        TargetFOV = SprintCameraFOV;
    }
    // TODO: Interpolate position instead of FOV for sliding and jumping
    else if (MovementHandlerComponent->IsSliding())
    {
        TargetFOV = SlideCameraFOV;
    }
    else if (MovementHandlerComponent->IsJumping())
    {
        TargetFOV = JumpCameraFOV;
    }
    else
    {
        TargetFOV = DefaultCameraFOV;
    }

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

    const float TargetOffset = MovementHandlerComponent->IsMovingRight() &&
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
void ALBPlayerCharacter::MoveCustom_Implementation(const FVector2D Value)
{
    MovementHandlerComponent->SetForwardInput(Value.Y);
    MovementHandlerComponent->SetRightInput(Value.X);
}

void ALBPlayerCharacter::LookCustom_Implementation(const FVector2D Value)
{
    MovementHandlerComponent->SetLookUpInput(-Value.Y);
    MovementHandlerComponent->SetTurnAroundInput(Value.X);
}

void ALBPlayerCharacter::JumpCustom_Implementation()
{
    MovementHandlerComponent->PerformJump();
}

void ALBPlayerCharacter::SprintCustom_Implementation(const bool bWantsToSprint)
{
    MovementHandlerComponent->Sprint(bWantsToSprint);
}

void ALBPlayerCharacter::SprintToggleCustom_Implementation()
{
    bSprintToggle = !bSprintToggle;
    MovementHandlerComponent->Sprint(bSprintToggle);
}

void ALBPlayerCharacter::CrouchCustom_Implementation(const bool bWantsToCrouch)
{
    MovementHandlerComponent->SlideOrCrouch(bWantsToCrouch);
}

void ALBPlayerCharacter::CrouchToggleCustom_Implementation()
{
    bCrouchToggle = !bCrouchToggle;
    MovementHandlerComponent->SlideOrCrouch(bCrouchToggle);
}

void ALBPlayerCharacter::WalkCustom_Implementation(const bool bWantsToWalk)
{
    MovementHandlerComponent->Walk(bWantsToWalk);
}

void ALBPlayerCharacter::WalkToggleCustom_Implementation()
{
    bWalkToggle = !bWalkToggle;

    MovementHandlerComponent->Walk(bWalkToggle);
}

void ALBPlayerCharacter::AimCustom_Implementation(const bool bWantsToAim)
{
    // Not yet implemented
    return;
}

void ALBPlayerCharacter::PickCustom_Implementation()
{
    // Not yet implemented
    return;
}

// Will probably be deleted later
void ALBPlayerCharacter::GetShadowCasterMesh_Implementation(
    USkeletalMeshComponent*& OutMesh)
{
    OutMesh = GetMesh();
}
