// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerController.h"

#include "LBSpectatorPawn.h"

#include "DelegateMediatorSubsystem.h"
#include "ECStateSubsystem.h"

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

void ALBPlayerController::BeginPlay()
{
    Super::BeginPlay();

    DelegateMediator = UDelegateMediatorSubsystem::Get(GetWorld());
    check(DelegateMediator);

    DelegateMediator->OnPlayerDeath.AddUObject(
        this, &ALBPlayerController::OnPawnDeath);
}

void ALBPlayerController::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
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

            if (!SIInputManager->OnActionPressed.GetAllObjects().Contains(
                    this))
            {
                SIInputManager->OnActionPressed.AddDynamic(
                    this, &ALBPlayerController::ProcessPressed);
            }

            if (!SIInputManager->OnActionHold.GetAllObjects().Contains(this))
            {
                SIInputManager->OnActionHold.AddDynamic(
                    this, &ALBPlayerController::ProcessHold);
            }

            if (!SIInputManager->OnActionReleased.GetAllObjects().Contains(
                    this))
            {
                SIInputManager->OnActionReleased.AddDynamic(
                    this, &ALBPlayerController::ProcessReleased);
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
    else if (ActionName == "LookUp" && AxisType == ESimpleInputAxisType::X)
    {
        PawnLookUp(Value);
    }
    else if (ActionName == "TurnAround" && AxisType == ESimpleInputAxisType::Y)
    {
        PawnTurnAround(Value);
    }
}

void ALBPlayerController::ProcessPressed(FName ActionName)
{
    if (ActionName == "Jump")
    {
        PawnJump();
    }
}

void ALBPlayerController::ProcessHold(FName ActionName)
{
    if (ActionName == "StartSprinting")
    {
        PawnStartSprinting();
    }
}

void ALBPlayerController::ProcessReleased(FName ActionName)
{
    if (ActionName == "StopSprinting")
    {
        PawnStopSprinting();
    }
}

void ALBPlayerController::MovePawnForward(float Value)
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_MoveForwardCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::MovePawnRight(float Value)
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_MoveRightCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::PawnLookUp(float Value)
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_LookUpCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::PawnTurnAround(float Value)
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_TurnAroundCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::PawnJump()
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_JumpCustom(GetPawn());
    }
}

void ALBPlayerController::PawnStartSprinting()
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_StartSprinting(GetPawn());
    }
}

void ALBPlayerController::PawnStopSprinting()
{
    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_StopSprinting(GetPawn());
    }
}

void ALBPlayerController::OnPawnDeath(APawn* Pawn)
{
    if (GetPawn() == Pawn)
    {
        if (UECStateSubsystem* ControllerState =
                UECStateSubsystem::Get(GetWorld()))
        {
            ControllerState->BeginSpectating(
                this, ALBSpectatorPawn::StaticClass());
        }
    }
}