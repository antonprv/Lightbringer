// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h"

#include "Engine/World.h"
#include "Animation/AnimMontage.h"

// Sets default values for this component's properties
ULBCharacterMovementComponent::ULBCharacterMovementComponent(
    const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    SprintSpeed = 1000.f;
    MovementSmoothingSpeed = 10.f;
    SprintSmoothingSpeed = 8.f;
    RotationSpeed = 540.f;
    RunTransitionDelay = 0.4f;
    JumpAirControl = 0.2f;

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
        DefaultWalkSpeed = MaxWalkSpeed;
    }

    bIsJumpAllowed = true;
}

void ULBCharacterMovementComponent::TickComponent(float DeltaTime,
    ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    SprintInterpolate();
}

void ULBCharacterMovementComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void ULBCharacterMovementComponent::SetIsJumpAllowed(bool Value)
{
    bIsJumpAllowed = Value;
}

void ULBCharacterMovementComponent::SetForwardInput(const float& Value)
{
    if (!CharacterOwner) return;

    UpdateDesiredRotation();

    bIsMovingForward = Value > 0;
    bIsMovingBack = Value < 0;
    bIsMoving = !FMath::IsNearlyZero(Value);

    // SetRunningRules();

    // find out which way is forward
    const FRotator Rotation = CharacterOwner->Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get forward vector
    const FVector Direction =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    if (FMath::IsNearlyEqual(CurrentFowrardValue, Value))
    {
        CharacterOwner->AddMovementInput(Direction, CurrentFowrardValue);
    }
    else
    {
        CurrentFowrardValue = FMath::FInterpTo(CurrentFowrardValue, Value,
            GetWorld()->GetDeltaSeconds(), MovementSmoothingSpeed);

        CharacterOwner->AddMovementInput(Direction, CurrentFowrardValue);
    }
}

void ULBCharacterMovementComponent::SetRightInput(const float& Value)
{
    if (!CharacterOwner) return;

    UpdateDesiredRotation();

    bIsMovingSideways = !FMath::IsNearlyZero(Value);
    bIsMovingRight = Value > 0;

    // find out which way is right
    const FRotator Rotation = CharacterOwner->Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // get right vector
    const FVector Direction =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if (FMath::IsNearlyEqual(CurrentRightValue, Value))
    {
        CharacterOwner->AddMovementInput(Direction, CurrentRightValue);
    }
    else
    {
        CurrentRightValue = FMath::FInterpTo(CurrentRightValue, Value,
            GetWorld()->GetDeltaSeconds(), MovementSmoothingSpeed);

        CharacterOwner->AddMovementInput(Direction, CurrentRightValue);
    }
}

void ULBCharacterMovementComponent::SetLookUpInput(const float& Value)
{
    if (!CharacterOwner) return;

    UpdateDesiredRotation();

    CharacterOwner->AddControllerPitchInput(Value);
}

void ULBCharacterMovementComponent::SetTurnAroundInput(const float& Value)
{
    if (!CharacterOwner) return;

    UpdateDesiredRotation();

    CharacterOwner->AddControllerYawInput(Value);
}

void ULBCharacterMovementComponent::PerformJump()
{
    if (!bIsJumpAllowed) return;
    
    UpdateDesiredRotation();

    CharacterOwner->Jump();
}

void ULBCharacterMovementComponent::SetLandingRules()
{
    bIsJumpAllowed = false;

    GetWorld()->GetTimerManager().SetTimer(JumpHandle, this,
        &ULBCharacterMovementComponent::AllowJumping, 0.01f, false, JumpDelay);
}

void ULBCharacterMovementComponent::AllowJumping()
{
    bIsJumpAllowed = true;

    JumpHandle.Invalidate();
}

void ULBCharacterMovementComponent::UpdateDesiredRotation()
{
    bUseControllerDesiredRotation = !CharacterOwner->GetVelocity().IsZero();
}

void ULBCharacterMovementComponent::Sprint(bool bWantsToSprint)
{
    if (IsSprintForbidden())
    {
        bCanSprint = false;
        return;
    };

    // only allow sprinting if we're moving forward or diagonally
    UpdateDesiredRotation();

    bCanSprint = bWantsToSprint;
}

void ULBCharacterMovementComponent::SprintInterpolate()
{
    if (!CharacterOwner) return;

    const float TargetMaxWalkSpeed =
        bCanSprint ? SprintSpeed : DefaultWalkSpeed;

    if (FMath::IsNearlyEqual(CurrentMaxWalkSpeed, TargetMaxWalkSpeed))
    {
        if (MaxWalkSpeed != TargetMaxWalkSpeed)
        {
            MaxWalkSpeed = TargetMaxWalkSpeed;
        }

        return;
    }

    CurrentMaxWalkSpeed =
        FMath::FInterpTo(CurrentMaxWalkSpeed, TargetMaxWalkSpeed,
            GetWorld()->GetDeltaSeconds(), SprintSmoothingSpeed);

    MaxWalkSpeed = CurrentMaxWalkSpeed;
}

bool ULBCharacterMovementComponent::IsSprintForbidden()
{
    return (!bIsMovingForward && bIsMovingSideways) || !bIsMovingForward;
}

bool ULBCharacterMovementComponent::IsSprinting()
{
    if (!CharacterOwner) return false;

    return bIsMovingForward && bCanSprint &&
           !CharacterOwner->GetVelocity().IsZero();
}