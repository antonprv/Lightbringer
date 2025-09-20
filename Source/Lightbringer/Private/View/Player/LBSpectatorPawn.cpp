// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBSpectatorPawn.h"

#include "GameFramework/PawnMovementComponent.h"

ALBSpectatorPawn::ALBSpectatorPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = true;
}

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