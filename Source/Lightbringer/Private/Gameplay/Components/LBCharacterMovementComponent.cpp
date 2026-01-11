// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h"

#include "Engine/World.h"

#include "MathUtilStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogULBCharacterMovementComponent, Log, Log)

// Sets default values for this component's properties
ULBCharacterMovementComponent::ULBCharacterMovementComponent(
    const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    SprintSpeed = 1000.f;
    WalkToSprintSmoothing = 10.f;
    BankingUpdateSmoothing = 10.f;
    BankingMultiplier = 10.f;
    RotationSpeed = 540.f;
    RunTransitionDelay = 0.4f;
    JumpAirControl = 0.2f;

    WalkingSpeed = 250.f;

    AirControl = JumpAirControl;
    RotationRate = {0, RotationSpeed, 0.f};
}

// Called when the game starts
void ULBCharacterMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    CharacterOwner = Cast<ACharacter>(GetOwner());

    if (CharacterOwner)
    {
        DefaultWalkSpeed = MaxWalkSpeed;  // 600.0f;
    }

    bIsJumpAllowed = true;

    if (!CharacterOwner->LandedDelegate.Contains(
            this, GET_FUNCTION_NAME_CHECKED(
                      ULBCharacterMovementComponent, OnCharacterLanding)))
    {
        CharacterOwner->LandedDelegate.AddDynamic(
            this, &ULBCharacterMovementComponent::OnCharacterLanding);
    }
}

void ULBCharacterMovementComponent::TickComponent(float DeltaTime,
    ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CheckSprintCondition();

    UpdateDesiredRotation();
    UpdateBanking();
    SpeedInterpolate();
}

void ULBCharacterMovementComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    if (CharacterOwner->LandedDelegate.Contains(
            this, GET_FUNCTION_NAME_CHECKED(
                      ULBCharacterMovementComponent, OnCharacterLanding)))
    {
        CharacterOwner->LandedDelegate.RemoveDynamic(
            this, &ULBCharacterMovementComponent::OnCharacterLanding);
    }

    Super::EndPlay(EndPlayReason);
}

void ULBCharacterMovementComponent::OnCharacterLanding(
    const FHitResult& HitResult)
{
    if (!GetWorld()) return;

    SetLandingRules();
}

void ULBCharacterMovementComponent::SetIsJumpAllowed(bool Value)
{
    bIsJumpAllowed = Value;
}

float ULBCharacterMovementComponent::GetDefaultWalkSpeed()
{
    return DefaultWalkSpeed;
}

float ULBCharacterMovementComponent::GetBanking()
{
    return Banking;
}

void ULBCharacterMovementComponent::SetForwardInput(const float Value)
{
    if (!CharacterOwner) return;

    bIsMovingForward = Value > 0;
    bIsMovingBack = Value < 0;

    // SetRunningRules();

    // find out which way is forward
    const FRotator Rotation = CharacterOwner->Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get forward vector
    const FVector Direction =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    CharacterOwner->AddMovementInput(Direction, Value);
}

void ULBCharacterMovementComponent::SetRightInput(const float Value)
{
    if (!CharacterOwner) return;

    bIsMovingSideways = !FMath::IsNearlyZero(Value);
    bIsMovingRight = Value > 0;
    bIsMovingLeft = Value < 0;

    // find out which way is right
    const FRotator Rotation = CharacterOwner->Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get right vector
    const FVector Direction =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    CharacterOwner->AddMovementInput(Direction, Value);
}

void ULBCharacterMovementComponent::SetLookUpInput(const float Value)
{
    if (!CharacterOwner) return;

    CharacterOwner->AddControllerPitchInput(Value);
}

void ULBCharacterMovementComponent::SetTurnAroundInput(const float Value)
{
    if (!CharacterOwner) return;

    NewBanking = Value * BankingMultiplier;

    CharacterOwner->AddControllerYawInput(Value);
}

void ULBCharacterMovementComponent::PerformJump()
{
    if (!bIsJumpAllowed) return;

    CharacterOwner->Jump();
}

void ULBCharacterMovementComponent::SetLandingRules()
{
    bIsJumpAllowed = false;

    GetWorld()->GetTimerManager().SetTimer(JumpHandle, this,
        &ULBCharacterMovementComponent::AllowJumping, 0.01f, false, JumpDelay);
}

void ULBCharacterMovementComponent::UpdateBanking()
{
    if (FMath::IsNearlyEqual(Banking, NewBanking)) return;

    Banking = FMath::FInterpConstantTo(Banking, NewBanking,
        GetWorld()->GetDeltaSeconds(), BankingUpdateSmoothing);
}

void ULBCharacterMovementComponent::AllowJumping()
{
    bIsJumpAllowed = true;

    JumpHandle.Invalidate();
}

// If Player is already sprinting, make sure he cannot sprint backwards
void ULBCharacterMovementComponent::CheckSprintCondition()
{
    if (bCanSprint)
    {
        bCanSprint = !bIsMovingBack;
    }
}

void ULBCharacterMovementComponent::UpdateDesiredRotation()
{
    bUseControllerDesiredRotation = !CharacterOwner->GetVelocity().IsZero();
}

void ULBCharacterMovementComponent::Sprint(const bool bWantsToSprint)
{
    if (IsSprintForbidden())
    {
        bCanSprint = false;
        return;
    }

    bCanSprint = bWantsToSprint;
}

void ULBCharacterMovementComponent::Walk(const bool bWantsToWalk)
{
    if (IsSprinting())
    {
        bCanWalk = false;
        return;
    }

    bCanWalk = bWantsToWalk;
}

void ULBCharacterMovementComponent::SpeedInterpolate()
{
    if (!CharacterOwner) return;

    float TargetMaxWalkSpeed;
    if (bCanSprint)
    {
        TargetMaxWalkSpeed = SprintSpeed;
    }
    else if (bCanWalk)
    {
        TargetMaxWalkSpeed = WalkingSpeed;
    }
    else
    {
        TargetMaxWalkSpeed = DefaultWalkSpeed;
    }

    if (FMath::IsNearlyEqual(
            CurrentMaxWalkSpeed, TargetMaxWalkSpeed, KINDA_SMALL_NUMBER))
    {
        if (MaxWalkSpeed != TargetMaxWalkSpeed)
        {
            MaxWalkSpeed = TargetMaxWalkSpeed;
        }

        return;
    }

    CurrentMaxWalkSpeed =
        FMath::FInterpTo(CurrentMaxWalkSpeed, TargetMaxWalkSpeed,
            GetWorld()->GetDeltaSeconds(), WalkToSprintSmoothing);

    MaxWalkSpeed = CurrentMaxWalkSpeed;
}

bool ULBCharacterMovementComponent::IsSprintForbidden()
{
    return !bIsMovingForward || bIsMovingSideways || bCanWalk ||
           CharacterOwner->GetVelocity().IsZero();
}

bool ULBCharacterMovementComponent::IsSprinting()
{
    if (!CharacterOwner) return false;

    return bCanSprint && !bCanWalk && bIsMovingForward &&
           !CharacterOwner->GetVelocity().IsZero();
}

bool ULBCharacterMovementComponent::IsWalkingCustom()
{
    if (!CharacterOwner) return false;

    return bCanWalk && !bCanSprint && !CharacterOwner->GetVelocity().IsZero();
}

bool ULBCharacterMovementComponent::IsMoving()
{
    return !CharacterOwner->GetVelocity().IsZero();
}

bool ULBCharacterMovementComponent::IsMovingRight()
{
    return bIsMovingRight;
}
