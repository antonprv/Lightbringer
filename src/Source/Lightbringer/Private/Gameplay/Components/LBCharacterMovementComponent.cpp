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
    GetNavAgentPropertiesRef().bCanCrouch = true;
    GetNavAgentPropertiesRef().bCanJump = true;
    bCanEverSlide = true;

    SprintingSpeed = 1000.f;
    WalkToSprintSmoothing = 10.f;
    BankingUpdateSmoothing = 10.f;
    BankingMultiplier = 10.f;
    RotationSpeed = 540.f;
    RunTransitionDelay = 0.4f;
    JumpAirControl = 0.2f;

    WalkingSpeed = 250.f;
    SlidingSpeed = 1250.f;

    AirControl = JumpAirControl;
    RotationRate = {0, RotationSpeed, 0.f};

    bHasLanded = true;
    bIsSlideAllowed = true;

    JumpDelay = 0.2f;
    SlideDelay = 0.2f;

    JumpZVelocity = 600.f;
    SlideJumpZVelocity = 800.f;
}

void ULBCharacterMovementComponent::SetCanEverJump(bool Value)
{
    GetNavAgentPropertiesRef().bCanJump = Value;
}

void ULBCharacterMovementComponent::SetCanEverCrouch(bool Value)
{
    GetNavAgentPropertiesRef().bCanCrouch = Value;
}

void ULBCharacterMovementComponent::SetCanEverSlide(bool Value)
{
    bCanEverSlide = false;
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

    DefaultJumpZVelocity = JumpZVelocity;

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
    CheckSlideCondition();

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

void ULBCharacterMovementComponent::UpdateDesiredRotation()
{
    bUseControllerDesiredRotation = !CharacterOwner->GetVelocity().IsZero();
}

float ULBCharacterMovementComponent::GetDefaultWalkSpeed()
{
    return DefaultWalkSpeed;
}

float ULBCharacterMovementComponent::GetBanking()
{
    return Banking;
}

// =====================================================================
// Process directional input
// =====================================================================
void ULBCharacterMovementComponent::SetForwardInput(const float Value)
{
    if (!CharacterOwner) return;

    bIsNoForwardInput = Value == 0;
    bIsMovingForward = Value > 0;
    bIsMovingBack = Value < 0;

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

// =====================================================================
// Process input for "vertical" actions
// =====================================================================
void ULBCharacterMovementComponent::PerformJump()
{
    if (!bIsJumpAllowed) return;

    bHasLanded = false;

    if (bCanSlideJump)
    {
        JumpZVelocity = SlideJumpZVelocity;
    }
    else
    {
        JumpZVelocity = DefaultJumpZVelocity;
    }

    CharacterOwner->Jump();
}

void ULBCharacterMovementComponent::SlideOrCrouch(const bool bWantsToCrouch)
{
    if (IsSlideForbidden())
    {
        if (bWantsToCrouch)
        {
            CharacterOwner->Crouch();
        }
        else if (!bWantsToCrouch)
        {
            CharacterOwner->UnCrouch();
        }
    }
    else if (!IsSlideForbidden())
    {
        bCanSlide = bWantsToCrouch && bIsSlideAllowed;
        bCanSlideJump = bCanSlide;
        SetSlidingRules();
    }
}

void ULBCharacterMovementComponent::OnCharacterLanding(
    const FHitResult& HitResult)
{
    if (!GetWorld()) return;

    SetLandingRules();
}

void ULBCharacterMovementComponent::SetLandingRules()
{
    bIsJumpAllowed = false;
    bHasLanded = true;
    bCanSlideJump = false;

    if (!JumpHandle.IsValid())
    {
        GetWorld()->GetTimerManager().SetTimer(JumpHandle, this,
            &ULBCharacterMovementComponent::AllowJumping, 0.01f, false,
            JumpDelay);
    }
}

void ULBCharacterMovementComponent::SetSlidingRules()
{
    bIsSlideAllowed = false;

    if (!SlideHandle.IsValid())
    {
        GetWorld()->GetTimerManager().SetTimer(SlideHandle, this,
            &ULBCharacterMovementComponent::AllowSliding, 0.01f, false,
            SlideDelay);
    }
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

void ULBCharacterMovementComponent::AllowSliding()
{
    bIsSlideAllowed = true;

    SlideHandle.Invalidate();
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
        TargetMaxWalkSpeed = SprintingSpeed;
    }
    else if (bCanWalk)
    {
        TargetMaxWalkSpeed = WalkingSpeed;
    }
    else if (bCanSlide)
    {
        TargetMaxWalkSpeed = SlidingSpeed;
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

// =====================================================================
// Condition state checks
// =====================================================================
void ULBCharacterMovementComponent::CheckSprintCondition()
{
    if (bCanSprint)
    {
        bCanSprint = !IsSprintForbidden();
    }
}

void ULBCharacterMovementComponent::CheckSlideCondition()
{
    if (bCanSlide)
    {
        bCanSlide = !IsSlideForbidden();
        bCanSlideJump = bCanSlide;
    }
}

bool ULBCharacterMovementComponent::IsSprintForbidden()
{
    return !bIsMovingForward || (bIsNoForwardInput && bIsMovingSideways) ||
           bCanWalk || !IsMoving();
}

bool ULBCharacterMovementComponent::IsSlideForbidden()
{
    return (bIsNoForwardInput && bIsMovingSideways) || bCanWalk ||
           !IsMoving() || IsCrouching() || !bCanEverSlide || IsJumping();
}

bool ULBCharacterMovementComponent::IsMovingForward()
{
    return IsMoving() && bIsMovingForward && !bIsMovingBack;
}

bool ULBCharacterMovementComponent::IsMovingRight()
{
    return bIsMovingRight;
}

// =====================================================================
// Animation state checks
// =====================================================================
bool ULBCharacterMovementComponent::IsSprinting()
{
    if (!CharacterOwner) return false;

    return bCanSprint && !bCanWalk && bIsMovingForward && IsMoving() &&
           !IsSliding() && !IsCrouching();
}

bool ULBCharacterMovementComponent::IsJumping()
{
    return IsFalling() && !bHasLanded;
}

bool ULBCharacterMovementComponent::IsSliding()
{
    return !(bIsNoForwardInput && bIsMovingSideways) && !bCanWalk &&
           !IsCrouching() && bCanSlide && !IsJumping();
}

bool ULBCharacterMovementComponent::IsWalkingCustom()
{
    if (!CharacterOwner) return false;

    return bCanWalk && !bCanSprint && IsMoving();
}

bool ULBCharacterMovementComponent::IsMoving()
{
    return !CharacterOwner->GetVelocity().IsZero();
}
