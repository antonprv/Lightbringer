// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "InputManager.h"
#include "GameFramework/PlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogInputManager, Log, Log);

UInputManager* UInputManager::Get()
{
    static TWeakObjectPtr<UInputManager> Instance;

    if (!Instance.IsValid())
    {
        Instance = NewObject<UInputManager>(GetTransientPackage());
        Instance->AddToRoot();
    }

    return Instance.Get();
}

void UInputManager::BindActionData(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    if (!InputComponent || !InputData)
    {
        UE_LOG(LogInputManager, Warning,
            TEXT("Cannot bind ActionData, UInputComponent or UInputActionData "
                 "are nullptr."))

        return;
    }

    AddManagerToRoot();

    if (InputActionData)
    {
        UE_LOG(LogInputManager, Warning,
            TEXT("Cannot bind InputActionData, already bound."))
        return;
    }

    InputActionData = InputData;

    BindKeys_Internal(InputComponent, InputData);
    BindAxis_Internal(InputComponent, InputData);

    UE_LOG(
        LogInputManager, Display, TEXT("Successfully bound InputActionData"))
}

void UInputManager::UnbindAll(UInputComponent* InputComponent)
{
    if (!InputComponent) return;

    if (InputActionData)
    {
        UE_LOG(LogInputManager, Warning,
            TEXT("Cannot bind InputActionData, already unbound."))
        return;
    }

    InputComponent->KeyBindings.Reset();
    InputComponent->AxisKeyBindings.Reset();

    InputActionData = nullptr;

    UE_LOG(
        LogInputManager, Display, TEXT("Successfully unbound InputActionData"))
}

/**
 * Changes input binding in runtime, all changes will be lost when the session
 * ends. You need to manually call BindActionData() after this.  Currently
 * for testing only.
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
 * session ends. You need to manually call BindActionData() after this.
 * Currently for testing only.
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

void UInputManager::AddManagerToRoot()
{
    if (!IsRooted())
    {
        AddToRoot();
    }
}

void UInputManager::BindKeys_Internal(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    // Setting up key actions
    for (const TPair<FName, FSimpleInputBinding> Binding : InputData->Bindings)
    {
        const FName ActionName = Binding.Key;
        const FSimpleInputBinding ActionBinding = Binding.Value;

        const FKey Key = ActionBinding.KeyToPress;

        FInputKeyBinding KeyBinding(
            Key, Binding.Value.EventType == ESimpleInputEventType::Pressed
                     ? IE_Pressed
                     : IE_Released);

        KeyBinding.bConsumeInput = true;
        KeyBinding.KeyDelegate.GetDelegateForManualSet().BindLambda(
            [this, ActionName]() { HandlePressed(ActionName); });

        InputComponent->KeyBindings.Add(KeyBinding);
    }
}

void UInputManager::BindAxis_Internal(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
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
        // AxisBinding.bConsumeInput = true;

        AxisBinding.AxisDelegate.GetDelegateForManualSet().BindLambda(
            [this, ActionName, AxisName = ActionBinding.Axis](float Value)
            { HandleAxis(ActionName, AxisName, Value); });

        InputComponent->AxisKeyBindings.Add(AxisBinding);
    }
}