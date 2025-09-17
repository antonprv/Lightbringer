// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerController.h"
#include "SimpleInputSubsystem.h"
#include "InputManager.h"
#include "Interfaces/PlayerControllable.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

ALBPlayerController::ALBPlayerController()
{
    InputActionData = LoadObject<UInputActionData>(
        nullptr, TEXT("InputActionData'/Game/Blueprints/Data/Input/"
                      "IAD_ThirdPersonControls.IAD_ThirdPersonControls'"));
}

void ALBPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (USimpleInputSubsystem* SISubsystem =
            USimpleInputSubsystem::Get(GetWorld()))
    {
        if (UInputManager* SIInputManager = SISubsystem->GetInputManager())
        {
            SIInputManager->SetActiveActionData(
                this, InputComponent, InputActionData);

            if (!SIInputManager->OnAxisChanged.GetAllObjects().Contains(this))
            {
                SIInputManager->OnAxisChanged.AddDynamic(
                    this, &ALBPlayerController::ProcessInput);
            }
        }
    }
}

void ALBPlayerController::ProcessInput(
    FName ActionName, ESimpleInputAxisType AxisType, float Value)
{
    if (ActionName == "MoveForward" && AxisType == ESimpleInputAxisType::X)
    {
        MovePawnForward(Value);
    }
    else if (ActionName == "MoveRight" && AxisType == ESimpleInputAxisType::Y)
    {
        MovePawnRight(Value);
    }
}

void ALBPlayerController::MovePawnForward(float Value)
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_MoveForward(GetPawn(), Value);
    }
}

void ALBPlayerController::MovePawnRight(float Value)
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_MoveRight(GetPawn(), Value);
    }
}
