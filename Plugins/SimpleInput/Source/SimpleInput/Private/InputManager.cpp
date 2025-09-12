// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "InputManager.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogInputManager, Log, Log);

void UInputManager::Init(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    if (!InputComponent || !InputData) return;

    this->AddToRoot();
    InputActionData = InputData;

    // Setting up key actions
    for (const TPair<FName, FSimpleInputBinding> Binding : InputData->Bindings)
    {
        const FName ActionName = Binding.Key;
        const FSimpleInputBinding ActionBinding = Binding.Value;

        const FKey Key = ActionBinding.KeyToPress;

        if (ActionBinding.EventType == ESimpleInputEventType::Pressed)
        {
            FInputKeyBinding KeyBinding(Key, IE_Pressed);
            KeyBinding.bConsumeInput = true;

            KeyBinding.KeyDelegate.GetDelegateForManualSet().BindLambda(
                [this, ActionName]() { HandlePressed(ActionName); });
            InputComponent->KeyBindings.Add(KeyBinding);
        }
        else if (ActionBinding.EventType == ESimpleInputEventType::Released)
        {
            FInputKeyBinding KeyBinding(Key, IE_Released);
            KeyBinding.bConsumeInput = true;

            KeyBinding.KeyDelegate.GetDelegateForManualSet().BindLambda(
                [this, ActionName]() { HandleReleased(ActionName); });
            InputComponent->KeyBindings.Add(KeyBinding);
        }
    }

    // Setting up axis actions
    for (const TPair<FName, FSimpleInputBindingAxis> Binding :
        InputData->AxisBindings)
    {
        const FName ActionName = Binding.Key;
        const FSimpleInputBindingAxis ActionBinding = Binding.Value;

        const FKey Key = ActionBinding.KeyToPress;
        const ESimpleInputAxisType AxisType = ActionBinding.Axis;

        FInputAxisKeyBinding AxisBinding(ActionName);
        AxisBinding.AxisKey = ActionBinding.KeyToPress;
        AxisBinding.AxisDelegate.GetDelegateForManualSet().BindLambda(
            [this, ActionName, AxisName = ActionBinding.Axis](float Value)
            { HandleAxis(ActionName, AxisName, Value); });
        InputComponent->AxisKeyBindings.Add(AxisBinding);
    }
}

/**
 * Changes input binding in runtime, all changes will be lost when the session
 * ends. Currently for testing only.
 *
 * @param ActionName Name of the action that should be changed
 * @param NewKey new key that sets this value
 */
void UInputManager::ChangeInputKey(FName& ActionName, FKey& NewKey)
{
    InputActionData->SetBinding(ActionName, NewKey);
}

/**
 * Changes input axis binding in runtime, all changes will be lost when the
 * session ends. Currently for testing only.
 *
 * @param ActionName Name of the action that should be changed
 * @param NewKey new key that sets this value
 */
void UInputManager::ChangeInputAxisKey(FName& ActionName, FKey& NewKey)
{
    InputActionData->SetAxisBinding(ActionName, NewKey);
}

void UInputManager::HandlePressed(FName ActionName)
{
    OnActionPressed.Broadcast(ActionName);
}

void UInputManager::HandleReleased(FName ActionName)
{
    OnActionReleased.Broadcast(ActionName);
}

void UInputManager::HandleAxis(
    FName AxisName, ESimpleInputAxisType AxisType, float Value)
{
    OnAxisChanged.Broadcast(AxisName, AxisType, Value);
}
