// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

#include "Engine/World.h"

// Sets default values for this component's properties
ULBCharacterMovementComponent::ULBCharacterMovementComponent()
{
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    //
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

void ULBCharacterMovementComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

// Called every frame
void ULBCharacterMovementComponent::TickComponent(float DeltaTime,
    ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    SprintInterp(DeltaTime);
}

void ULBCharacterMovementComponent::SetIsJumpAllowed(bool Value)
{
    bIsJumpAllowed = Value;
}

void ULBCharacterMovementComponent::SetForwardInput(const float& Value)
{
    if (!CharacterOwner) return;

    bIsMovingForward = Value > 0;
    bIsMoving = Value != 0;

    bOrientRotationToMovement = bIsMovingForward;

    CharacterOwner->bUseControllerRotationYaw = Value < 0;

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
        CurrentFowrardValue = FMath::FInterpConstantTo(CurrentFowrardValue,
            Value, GetWorld()->GetDeltaSeconds(), MovementSmoothingSpeed);
        CharacterOwner->AddMovementInput(Direction, CurrentFowrardValue);
    }
}

void ULBCharacterMovementComponent::SetRightInput(const float& Value)
{
    if (!CharacterOwner) return;

    bIsMovingSideways = Value != 0;

    // Use left-right animations with no character rotation when A\D keys are
    // pressed, and no forward input received
    CharacterOwner->bUseControllerRotationYaw =
        bIsMovingSideways && !bIsMoving;

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
        CurrentRightValue = FMath::FInterpConstantTo(CurrentRightValue, Value,
            GetWorld()->GetDeltaSeconds(), MovementSmoothingSpeed);
        CharacterOwner->AddMovementInput(Direction, CurrentRightValue);
    }
}

void ULBCharacterMovementComponent::SetLookUpInput(const float& Value)
{
    if (!CharacterOwner) return;

    CharacterOwner->AddControllerPitchInput(Value);
}

void ULBCharacterMovementComponent::SetTurnAroundInput(const float& Value)
{
    if (!CharacterOwner) return;

    CharacterOwner->AddControllerYawInput(Value);
}

void ULBCharacterMovementComponent::SetStartSprinting()
{
    if (!CharacterOwner) return;

    if (IsSprintForbidden()) return;

    bWantsToSprint = true;
}

void ULBCharacterMovementComponent::SetStopSprinting()
{
    bWantsToSprint = false;
}

void ULBCharacterMovementComponent::PerformJump()
{
    if (!bIsJumpAllowed) return;

    CharacterOwner->Jump();
}

void ULBCharacterMovementComponent::SprintInterp(float DeltaTime)
{
    if (!CharacterOwner) return;

    // only allow sprinting if we're moving forward or diagonally
    if (IsSprintForbidden())
    {
        bWantsToSprint = false;
    }

    const float TargetMaxWalkSpeed =
        bWantsToSprint ? SprintSpeed : DefaultWalkSpeed;

    if (FMath::IsNearlyEqual(
            CurrentMaxWalkSpeed, TargetMaxWalkSpeed, KINDA_SMALL_NUMBER))
    {
        if (MaxWalkSpeed != TargetMaxWalkSpeed)
        {
            MaxWalkSpeed = TargetMaxWalkSpeed;
        }

        return;
    }

    CurrentMaxWalkSpeed = FMath::FInterpTo(CurrentMaxWalkSpeed,
        TargetMaxWalkSpeed, DeltaTime, SprintSmoothingSpeed);

    MaxWalkSpeed = CurrentMaxWalkSpeed;
}

bool ULBCharacterMovementComponent::IsSprintForbidden()
{
    return (!bIsMovingForward && bIsMovingSideways) || !bIsMovingForward ||
           !IsMovingOnGround();
}

bool ULBCharacterMovementComponent::IsSprinting()
{
    if (!CharacterOwner) return false;

    return bIsMovingForward && bWantsToSprint &&
           !CharacterOwner->GetVelocity().IsZero();
}