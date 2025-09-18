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
    void MoveForward(float& Value);
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void MoveRight(float& Value);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void LookUp(float& Value);
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void TurnAround(float& Value);
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void JumpUp();
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void StartSprinting();
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void StopSprinting();

    virtual void MoveForward_Implementation(float& Value) = 0;
    virtual void MoveRight_Implementation(float& Value) = 0;
    virtual void LookUp_Implementation(float& Value) = 0;
    virtual void TurnAround_Implementation(float& Value) = 0;
    virtual void JumpUp_Implementation() = 0;
    virtual void StartSprinting_Implementation() = 0;
    virtual void StopSprinting_Implementation() = 0;
};
