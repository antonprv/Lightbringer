// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBSpectatorPawn.h"
#include "PlayerDelegateMediator.h"

#include "Engine/World.h"

#include "GameFramework/PawnMovementComponent.h"

/*
 * Initialize parameters
 */
ALBSpectatorPawn::ALBSpectatorPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = true;

    Speed = 1.f;
    SprintSpeed = 10.f;
}

void ALBSpectatorPawn::BeginPlay()
{
    Super::BeginPlay();

    if (!OnDestroyed.Contains(this,
            GET_FUNCTION_NAME_CHECKED(ALBSpectatorPawn, HandleDestruction)))
    {
        OnDestroyed.AddDynamic(this, &ALBSpectatorPawn::HandleDestruction);
    }
}

void ALBSpectatorPawn::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    if (OnDestroyed.Contains(this,
            GET_FUNCTION_NAME_CHECKED(ALBSpectatorPawn, HandleDestruction)))
    {
        OnDestroyed.RemoveDynamic(this, &ALBSpectatorPawn::HandleDestruction);
    }

    Super::EndPlay(EndPlayReason);
}

/*
 * Callback functions
 */
void ALBSpectatorPawn::HandleDestruction(AActor* DestroyedActor)
{
    if (!GetWorld()) return;

    if (UPlayerDelegateMediator* DelegateMediator =
            UPlayerDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerDestruction(DestroyedActor);
    }
}

void ALBSpectatorPawn::ToggleSprint(const bool bCanSprint) 
{
    if (bCanSprint)
    {
        Speed = SprintSpeed;
    }
}

/*
 * Interface implementation
 */
void ALBSpectatorPawn::MoveCustom_Implementation(const FVector2D Value) 
{
    MoveForward(Value.Y * Speed);
    MoveRight(Value.X * Speed);
}

void ALBSpectatorPawn::LookCustom_Implementation(const FVector2D Value) 
{
    AddControllerPitchInput(-Value.Y);
    AddControllerYawInput(Value.X);
}

void ALBSpectatorPawn::JumpCustom_Implementation()
{
    AddMovementInput(GetActorUpVector(), Speed);
}

void ALBSpectatorPawn::SprintToggleCustom_Implementation() 
{
    bSprintToggle = !bSprintToggle;
    ToggleSprint(bSprintToggle);
}

void ALBSpectatorPawn::SprintCustom_Implementation(const bool bWantsToSprint)
{
    ToggleSprint(bWantsToSprint);
}

void ALBSpectatorPawn::CrouchCustom_Implementation(const bool bWantsToCrouch)
{
    // Not implemented
    return;
}

void ALBSpectatorPawn::CrouchToggleCustom_Implementation() 
{
    // Not implemented
    return;
}

void ALBSpectatorPawn::WalkCustom_Implementation(const bool bWantsToWalk) 
{
    // Not implemented
    return;
}

void ALBSpectatorPawn::WalkToggleCustom_Implementation() 
{
    // Not implemented
    return;
}

void ALBSpectatorPawn::AimCustom_Implementation(const bool bWantsToAim) 
{
    // Not implemented
    return;
}

void ALBSpectatorPawn::PickCustom_Implementation() 
{
    // Not implemented
    return;
}
