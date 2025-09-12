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
        Instance->AddToRoot();  // prevent GC if you want it alive for whole
                                // runtime
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

void UInputManager::UnbindActionData(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    if (!InputComponent || !InputData) return;

    if (InputActionData)
    {
        UE_LOG(LogInputManager, Warning,
            TEXT("Cannot bind InputActionData, already unbound."))
        return;
    }

    // Keys
    for (const auto& Pair : InputData->Bindings)
    {
        if (FInputKeyBinding** Found = CreatedBindings.Find(Pair.Key))
        {
            InputComponent->KeyBindings.RemoveSingle(**Found);
            CreatedBindings.Remove(Pair.Key);
        }
    }

    // Axes
    for (const auto& Pair : InputData->AxisBindings)
    {
        if (FInputAxisKeyBinding** Found = CreatedAxisBindings.Find(Pair.Key))
        {
            InputComponent->AxisKeyBindings.RemoveSingle(**Found);
            CreatedAxisBindings.Remove(Pair.Key);
        }
    }

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

        FInputKeyBinding NewBinding(
            Key, Binding.Value.EventType == ESimpleInputEventType::Pressed
                     ? IE_Pressed
                     : IE_Released);

        NewBinding.bConsumeInput = true;
        NewBinding.KeyDelegate.GetDelegateForManualSet().BindLambda(
            [this, ActionName]() { HandlePressed(ActionName); });

        FInputKeyBinding* Added =
            &InputComponent->KeyBindings.Add_GetRef(NewBinding);

        CreatedBindings.FindOrAdd(ActionName, Added);
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

        FInputAxisKeyBinding* Added =
            &InputComponent->AxisKeyBindings.Add_GetRef(AxisBinding);

        CreatedAxisBindings.FindOrAdd(ActionName, Added);
    }
}