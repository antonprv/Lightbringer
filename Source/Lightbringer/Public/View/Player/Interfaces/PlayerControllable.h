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
    void MoveForwardCustom(const float& Value);
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void MoveRightCustom(const float& Value);

    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void LookUpCustom(const float& Value);
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void TurnAroundCustom(const float& Value);
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void JumpCustom();
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void StartSprinting();
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void StopSprinting();

    virtual void MoveForwardCustom_Implementation(const float& Value) = 0;
    virtual void MoveRightCustom_Implementation(const float& Value) = 0;
    virtual void LookUpCustom_Implementation(const float& Value) = 0;
    virtual void TurnAroundCustom_Implementation(const float& Value) = 0;
    virtual void JumpCustom_Implementation() = 0;
    virtual void StartSprinting_Implementation() = 0;
    virtual void StopSprinting_Implementation() = 0;
};
