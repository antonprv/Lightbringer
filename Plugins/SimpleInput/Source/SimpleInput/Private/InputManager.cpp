// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "InputManager.h"
#include "InputActionData.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/World.h"

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

void UInputManager::SetActiveActionData(APlayerController* PlayerController,
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    if (!InputComponent || !InputData || !PlayerController)
    {
        UE_LOG(LogInputManager, Warning,
            TEXT("Failed to bind ActionData: either the UInputComponent, "
                 "UInputActionData, or PlayerController is null."))

        return;
    }

    UnbindAll(InputComponent);

    InputActionData = InputData;

    __Internal_BindKeys(InputComponent, InputData);
    __Internal_BindAxis(PlayerController, InputComponent, InputData);

    UE_LOG(
        LogInputManager, Display, TEXT("Successfully bound InputActionData"))

    UE_LOG(LogInputManager, Display,
        TEXT("KeyBindings: %d, AxisKeyBindings: %d"),
        InputComponent->KeyBindings.Num(),
        InputComponent->AxisKeyBindings.Num());
}

void UInputManager::UnbindAll(UInputComponent* InputComponent)
{
    if (!InputComponent || !InputActionData) return;

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

void UInputManager::HandleHold(FName ActionName)
{
    OnActionHold.Broadcast(ActionName);
}

void UInputManager::HandleDoubleClick(FName ActionName)
{
    OnActionDoubleClick.Broadcast(ActionName);
}

void UInputManager::HandleAxis(
    FName AxisName, ESimpleInputAxisType AxisType, float Value)
{
    OnAxisChanged.Broadcast(AxisName, AxisType, Value);
}

void UInputManager::__Internal_BindKeys(
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    if (InputData->Bindings.Num() == 0) return;

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

            KeyBinding.bConsumeInput = false;

            switch (ActionBinding.EventType)
            {
                case ESimpleInputEventType::Pressed:
                    KeyBinding.KeyEvent = EInputEvent::IE_Pressed;
                    KeyBinding.KeyDelegate.GetDelegateForManualSet()
                        .BindLambda([this, ActionName]()
                            { HandlePressed(ActionName); });
                    break;
                case ESimpleInputEventType::Released:
                    KeyBinding.KeyEvent = EInputEvent::IE_Released;
                    KeyBinding.KeyDelegate.GetDelegateForManualSet()
                        .BindLambda([this, ActionName]()
                            { HandleReleased(ActionName); });
                    break;
                case ESimpleInputEventType::Hold:
                    KeyBinding.KeyEvent = EInputEvent::IE_Repeat;
                    KeyBinding.KeyDelegate.GetDelegateForManualSet()
                        .BindLambda(
                            [this, ActionName]() { HandleHold(ActionName); });
                    break;
                case ESimpleInputEventType::DoubleClick:
                    KeyBinding.KeyEvent = EInputEvent::IE_DoubleClick;
                    KeyBinding.KeyDelegate.GetDelegateForManualSet()
                        .BindLambda([this, ActionName]()
                            { HandleDoubleClick(ActionName); });
                    break;
                default: break;
            }

            InputComponent->KeyBindings.Add(KeyBinding);
        }
    }
}

void UInputManager::__Internal_BindAxis(APlayerController* PlayerController,
    UInputComponent* InputComponent, UInputActionData* InputData)
{
    if (!InputData || !PlayerController || !InputComponent ||
        InputData->AxisBindings.Num() == 0)
        return;

    for (const TPair<FName, FSimpleInputBindingAxisArray>& Bindings :
        InputData->AxisBindings)
    {
        const FName ActionName = Bindings.Key;

        for (const FSimpleInputBindingAxis& AxisBindingInfo :
            Bindings.Value.Bindings)
        {
            const FKey Key = AxisBindingInfo.KeyToPress;

            const ESimpleInputAxisType AxisType = AxisBindingInfo.Axis;
            const float Scale = AxisBindingInfo.Scale;

            if (Key.IsAxis1D())
            {
                auto& AxisKeyBinding =
                    InputComponent->AxisKeyBindings.Add_GetRef(
                        FInputAxisKeyBinding(Key));
                AxisKeyBinding.bConsumeInput = false;
                AxisKeyBinding.AxisDelegate.GetDelegateForManualSet()
                    .BindLambda(
                        [this, ActionName, AxisType, Scale](float Value)
                        { HandleAxis(ActionName, AxisType, Value * Scale); });
            }
            else
            {
                FInputAxisBinding& AxisBinding =
                    InputComponent->BindAxis(ActionName);
                AxisBinding.AxisDelegate.GetDelegateForManualSet().BindLambda(
                    [this, ActionName, AxisType](float Value)
                    { HandleAxis(ActionName, AxisType, Value); });

                PlayerController->PlayerInput->AddAxisMapping(
                    FInputAxisKeyMapping(ActionName, Key, Scale));
            }
        }
    }
}