// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Object.h"
#include "InputActionData.h"
#include "Components/InputComponent.h"
#include "InputManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputAction, FName, ActionName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInputActionAxis, FName,
    ActionName, ESimpleInputAxisType, Axis, float, AxisValue);

UCLASS(Blueprintable)
class SIMPLEINPUT_API UInputManager : public UObject
{
    GENERATED_BODY()

public:
    static UInputManager* Get();

    UFUNCTION(BlueprintCallable)
    void BindActionData(
        class UInputComponent* InputComponent, UInputActionData* InputData);
    UFUNCTION(BlueprintCallable)
    void UnbindAll(class UInputComponent* InputComponent);

    UFUNCTION(BlueprintCallable)
    void ChangeInputKey(FName& ActionName, FKey& NewKey);
    UFUNCTION(BlueprintCallable)
    void ChangeInputAxisKey(FName& ActionName, FKey& NewKey);

    UPROPERTY(BlueprintAssignable)
    FOnInputAction OnActionPressed;

    UPROPERTY(BlueprintAssignable)
    FOnInputAction OnActionReleased;

    UPROPERTY(BlueprintAssignable)
    FOnInputActionAxis OnAxisChanged;

private:
    UPROPERTY() UInputActionData* InputActionData { nullptr };

    void HandlePressed(FName ActionName);
    void HandleReleased(FName ActionName);
    void HandleAxis(
        FName AxisName, ESimpleInputAxisType AxisType, float Value);

    void AddManagerToRoot();

    void BindKeys_Internal(
        UInputComponent* InputComponent, UInputActionData* InputData);

    void BindAxis_Internal(
        UInputComponent* InputComponent, UInputActionData* InputData);
};
