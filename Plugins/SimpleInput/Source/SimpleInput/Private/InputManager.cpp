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

void UInputManager::SetActiveActionData(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    if (!InputComponent || !InputData)
    {
        UE_LOG(LogInputManager, Warning,
            TEXT("Cannot bind ActionData, UInputComponent or UInputActionData "
                 "are nullptr."))

        return;
    }

    if (InputActionData)
    {
        UE_LOG(LogInputManager, Warning,
            TEXT("Cannot bind InputActionData, already bound."))
        return;
    }

    UnbindAll(InputComponent);

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

void UInputManager::BindKeys_Internal(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    // Setting up key actions
    for (const TPair<FName, FSimpleInputBindingArray>& Bindings :
        InputData->Bindings)
    {
        const FName ActionName = Bindings.Key;

        for (FSimpleInputBinding ActionBinding : Bindings.Value.Bindings)
        {
            const FInputChord KeyChord(ActionBinding.KeyToPress);

            FInputKeyBinding KeyBinding;

            KeyBinding.Chord = KeyChord;
            KeyBinding.KeyEvent =
                ActionBinding.EventType == ESimpleInputEventType::Pressed
                    ? IE_Pressed
                    : IE_Released;

            KeyBinding.bConsumeInput = false;

            KeyBinding.KeyDelegate.GetDelegateForManualSet().BindLambda(
                [this, ActionName]() { HandlePressed(ActionName); });

            InputComponent->KeyBindings.Add(KeyBinding);
        }
    }
}

void UInputManager::BindAxis_Internal(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    // Setting up axis actions
    for (const TPair<FName, FSimpleInputBindingAxisArray>& Bindings :
        InputData->AxisBindings)
    {
        const FName ActionName = Bindings.Key;

        for (FSimpleInputBindingAxis AcionAxisBinding :
            Bindings.Value.Bindings)
        {
            const FKey Key = AcionAxisBinding.KeyToPress;
            const ESimpleInputAxisType AxisType = AcionAxisBinding.Axis;

            FInputAxisKeyBinding AxisBinding;
            AxisBinding.AxisKey = AcionAxisBinding.KeyToPress;

            AxisBinding.bConsumeInput = false;

            AxisBinding.AxisDelegate.GetDelegateForManualSet().BindLambda(
                [this, ActionName, AxisName = AcionAxisBinding.Axis](
                    float Value) { HandleAxis(ActionName, AxisName, Value); });

            InputComponent->AxisKeyBindings.Add(AxisBinding);
        }
    }
}