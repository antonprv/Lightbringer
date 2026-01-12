// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "PlayerControllable.generated.h"

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
    void SprintCustom(const bool bWantsToSprint);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void SprintToggleCustom();

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void CrouchCustom(const bool bWantsToCrouch);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void CrouchToggleCustom();

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void WalkCustom(const bool bWantsToWalk);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void WalkToggleCustom();

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void AimCustom(const bool bWantsToAim);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void PickCustom();
    
    virtual void MoveCustom_Implementation(const FVector2D Value) =0;
    virtual void LookCustom_Implementation(const FVector2D Value) =0;
    virtual void JumpCustom_Implementation() =0;
    virtual void SprintCustom_Implementation(const bool bWantsToSprint) =0;
    virtual void SprintToggleCustom_Implementation() =0;
    virtual void CrouchCustom_Implementation(const bool bWantsToCrouch) =0;
    virtual void CrouchToggleCustom_Implementation() = 0;
    virtual void WalkCustom_Implementation(const bool bWantsToWalk) = 0;
    virtual void WalkToggleCustom_Implementation() =0;
    virtual void AimCustom_Implementation(const bool bWantsToAim) =0;
    virtual void PickCustom_Implementation() =0;
};
