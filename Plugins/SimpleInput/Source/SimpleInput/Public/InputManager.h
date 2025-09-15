// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "InputManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputAction, FName, ActionName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInputActionAxis, FName,
    ActionName, ESimpleInputAxisType, Axis, float, AxisValue);

class UInputActionData;
class UInputComponent;
class APlayerController;

UCLASS(Blueprintable)
class SIMPLEINPUT_API UInputManager : public UObject
{
    GENERATED_BODY()

public:
    static UInputManager* Get();

    UFUNCTION(BlueprintCallable)
    void SetActiveActionData(APlayerController* PlayerController,
        UInputComponent* InputComponent, UInputActionData* InputData);
    UFUNCTION(BlueprintCallable)
    void UnbindAll(class UInputComponent* InputComponent);

    UPROPERTY(BlueprintAssignable)
    FOnInputAction OnActionPressed;

    UPROPERTY(BlueprintAssignable)
    FOnInputAction OnActionReleased;

    UPROPERTY(BlueprintAssignable)
    FOnInputActionAxis OnAxisChanged;

private:
    UPROPERTY()
    UInputActionData* InputActionData{nullptr};

    void HandlePressed(FName ActionName);
    void HandleReleased(FName ActionName);
    void HandleAxis(
        FName AxisName, ESimpleInputAxisType AxisType, float Value);

    void __Internal_BindKeys(
        UInputComponent* InputComponent, UInputActionData* InputData);

    void __Internal_BindAxis(APlayerController* PlayerController,
        UInputComponent* InputComponent, UInputActionData* InputData);
};
