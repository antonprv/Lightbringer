// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Player/Interfaces/PlayerControllable.h"
#include "Data/Player/PlayerInputState.h"

// Add default functionality here for any IPlayerControllable functions that
// are not pure virtual.

void IPlayerControllable::SetCharacterInputState_Implementation(
    const FPlayerInputState& PlayerInputState)
{
    return;
}

void IPlayerControllable::MoveCustom_Implementation(const FVector2D Value)
{
    return;
}

void IPlayerControllable::LookCustom_Implementation(const FVector2D Value) 
{
    return;
}
void IPlayerControllable::JumpCustom_Implementation() 
{
    return;
}

void IPlayerControllable::Sprint_Implementation(const bool bWantsToSprint) 
{
    return;
}

void IPlayerControllable::Crouch_Implementation(const bool bWantsToCrouch) 
{
    return;
}
void IPlayerControllable::Walk_Implementation(const bool bWantsToWalk) 
{
    return;
}
void IPlayerControllable::Aim_Implementation(const bool bWantsToAim) 
{
    return;
}
void IPlayerControllable::PickUp_Implementation() 
{
    return;
}