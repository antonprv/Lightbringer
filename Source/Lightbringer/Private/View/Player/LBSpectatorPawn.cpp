// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Player/LBSpectatorPawn.h"
#include "View/Player/PlayerDelegateMediator.h"

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
void ALBSpectatorPawn::MoveForwardCustom_Implementation(const float& Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void ALBSpectatorPawn::MoveRightCustom_Implementation(const float& Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ALBSpectatorPawn::LookUpCustom_Implementation(const float& Value)
{
    AddControllerPitchInput(Value);
}

void ALBSpectatorPawn::TurnAroundCustom_Implementation(const float& Value)
{
    AddControllerYawInput(Value);
}

void ALBSpectatorPawn::JumpCustom_Implementation()
{
    // Not implemented
}

void ALBSpectatorPawn::StartSprinting_Implementation()
{
    // Not implemented
}

void ALBSpectatorPawn::StopSprinting_Implementation()
{
    // Not implemented
}
