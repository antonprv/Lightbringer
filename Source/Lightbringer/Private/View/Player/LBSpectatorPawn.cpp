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

    UpSpeed = 1.f;
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

/*
 * Interface implementation
 */
void ALBSpectatorPawn::MoveCustom_Implementation(const FVector2D Value) 
{
    MoveForward(Value.Y);
    MoveRight(Value.X);
}

void ALBSpectatorPawn::LookCustom_Implementation(const FVector2D Value) 
{
    AddControllerPitchInput(-Value.Y);
    AddControllerYawInput(Value.X);
}

void ALBSpectatorPawn::JumpCustom_Implementation()
{
    AddMovementInput(GetActorUpVector(), UpSpeed);
}

void ALBSpectatorPawn::SprintCustom_Implementation(const bool bWantsToSprint)
{
    // Not implemented
    return;
}

void ALBSpectatorPawn::CrouchCustom_Implementation(const bool bWantsToCrouch)
{
    // Not implemented
    return;
}

void ALBSpectatorPawn::WalkCustom_Implementation(const bool bWantsToWalk) 
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
