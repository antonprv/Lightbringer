// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "PlayerControllable.generated.h"

struct FPlayerInputState;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPlayerControllable : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class LIGHTBRINGER_API IPlayerControllable
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be
    // inherited to implement this interface.
public:
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void MoveCustom(const FVector2D Value);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void LookCustom(const FVector2D Value);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void JumpCustom();

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void Sprint(const bool bWantsToSprint);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void Crouch(const bool bWantsToCrouch);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void Walk(const bool bWantsToWalk);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void Aim(const bool bWantsToAim);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void PickUp();
    
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void SetCharacterInputState(const FPlayerInputState& PlayerInputState);

    virtual void SetCharacterInputState_Implementation(
        const FPlayerInputState& PlayerInputState);

    virtual void MoveCustom_Implementation(const FVector2D Value);
    virtual void LookCustom_Implementation(const FVector2D Value);
    virtual void JumpCustom_Implementation();
    virtual void Sprint_Implementation(const bool bWantsToSprint);
    virtual void Crouch_Implementation(const bool bWantsToCrouch);
    virtual void Walk_Implementation(const bool bWantsToWalk);
    virtual void Aim_Implementation(const bool bWantsToAim);
    virtual void PickUp_Implementation();
};
