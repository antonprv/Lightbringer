// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerController.h"

#include "LBSpectatorPawn.h"

#include "PlayerDelegateMediator.h"
#include "ECStateSubsystem.h"

#include "SimpleInputSubsystem.h"
#include "InputManager.h"

#include "Interfaces/PlayerControllable.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

/*
 * Initial controller setup
 */
ALBPlayerController::ALBPlayerController()
{
    InputActionData = LoadObject<UInputActionData>(
        nullptr, TEXT("InputActionData'/Game/Blueprints/Data/Input/"
                      "IAD_ThirdPersonControls.IAD_ThirdPersonControls'"));
}

void ALBPlayerController::BeginPlay()
{
    Super::BeginPlay();

    DelegateMediator = UPlayerDelegateMediator::Get(GetWorld());
    check(DelegateMediator);

    if (!DelegateMediator->OnPlayerDeath.IsBoundToObject(this))
    {
        DelegateMediator->OnPlayerDeath.AddUObject(
            this, &ALBPlayerController::OnPawnDeath);
    }

    if (!DelegateMediator->OnPlayerDestruction.IsBoundToObject(this))
    {
        DelegateMediator->OnPlayerDestruction.AddUObject(
            this, &ALBPlayerController::OnPawnDestruction);
    }
}

void ALBPlayerController::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    DelegateMediator->OnPlayerDeath.RemoveAll(this);
    DelegateMediator->OnPlayerDestruction.RemoveAll(this);

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

            if (!SIInputManager->OnAxisChanged.Contains(
                    this, GET_FUNCTION_NAME_CHECKED(
                              ALBPlayerController, ProcessInput)))
            {
                SIInputManager->OnAxisChanged.AddDynamic(
                    this, &ALBPlayerController::ProcessInput);
            }

            if (!SIInputManager->OnActionPressed.Contains(
                    this, GET_FUNCTION_NAME_CHECKED(
                              ALBPlayerController, ProcessPressed)))
            {
                SIInputManager->OnActionPressed.AddDynamic(
                    this, &ALBPlayerController::ProcessPressed);
            }

            if (!SIInputManager->OnActionHold.Contains(
                    this, GET_FUNCTION_NAME_CHECKED(
                              ALBPlayerController, ProcessHold)))
            {
                SIInputManager->OnActionHold.AddDynamic(
                    this, &ALBPlayerController::ProcessHold);
            }

            if (!SIInputManager->OnActionReleased.Contains(
                    this, GET_FUNCTION_NAME_CHECKED(
                              ALBPlayerController, ProcessReleased)))
            {
                SIInputManager->OnActionReleased.AddDynamic(
                    this, &ALBPlayerController::ProcessReleased);
            }
        }
    }
}

/*
 * Bind functions to input delegates.
 */
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

/*
 * Process input
 */
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

/*
 * Additional pawn callback functions
 */
void ALBPlayerController::OnPawnDeath(APawn* PlayerPawn)
{
    if (!GetPawn()) return;

    if (GetPawn() == PlayerPawn)
    {
        if (UECStateSubsystem* ControllerState =
                UECStateSubsystem::Get(GetWorld()))
        {
            ControllerState->BeginSpectating(
                this, ALBSpectatorPawn::StaticClass());
        }
    }
}

void ALBPlayerController::OnPawnDestruction(AActor* DestroyedPawnActor)
{
    if (!DestroyedPawnActor) return;

    if (UECStateSubsystem* ControllerState =
            UECStateSubsystem::Get(GetWorld()))
    {
        ControllerState->BeginSpectating(
            this, ALBSpectatorPawn::StaticClass());
    }
}

/*
 * Control pawn through pawn interface
 */
void ALBPlayerController::MovePawnForward(float Value)
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_MoveForwardCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::MovePawnRight(float Value)
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_MoveRightCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::PawnLookUp(float Value)
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_LookUpCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::PawnTurnAround(float Value)
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_TurnAroundCustom(GetPawn(), Value);
    }
}

void ALBPlayerController::PawnJump()
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_JumpCustom(GetPawn());
    }
}

void ALBPlayerController::PawnStartSprinting()
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_StartSprinting(GetPawn());
    }
}

void ALBPlayerController::PawnStopSprinting()
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_StopSprinting(GetPawn());
    }
}