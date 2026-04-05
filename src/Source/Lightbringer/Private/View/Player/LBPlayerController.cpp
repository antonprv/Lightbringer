// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Player/LBPlayerController.h"

#include "View/Player/LBSpectatorPawn.h"

#include "View/Player/PlayerDelegateMediator.h"
#include "ECStateSubsystem.h"

#include "View/Player/Interfaces/PlayerControllable.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

#include "GameFramework/GameState.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

/*
 * Initial controller setup
 */

void ALBPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LP = GetLocalPlayer())
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            Subsystem->AddMappingContext(InputMappingContext, 0);

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

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                GetLocalPlayer()))
    {
        if (InputMappingContext)
        {
            Subsystem->RemoveMappingContext(InputMappingContext);
        }
    }

    Super::EndPlay(EndPlayReason);
}

void ALBPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* Input =
            Cast<UEnhancedInputComponent>(InputComponent))
    {
        //
    }
}

/*
 * Additional pawn callback functions
 */
void ALBPlayerController::OnPawnDeath(APawn* PlayerPawn)
{
    if (!GetPawn() || !GetWorld()) return;

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
    if (!DestroyedPawnActor || !GetWorld()) return;

    if (UECStateSubsystem* ControllerState =
            UECStateSubsystem::Get(GetWorld()))
    {
        if (ControllerState->IsSpectating())
        {
            ControllerState->RespawnInWorld(this);
        }

        ControllerState->BeginSpectating(
            this, ALBSpectatorPawn::StaticClass());
    }
}

/*
 * Control pawn through pawn interface
 */

void ALBPlayerController::PawnMove(const FInputActionInstance& Instance)
{
    if (Instance.GetValue().GetValueType() == EInputActionValueType::Axis2D)
    {
        if (GetPawn()->GetClass()->ImplementsInterface(
                UPlayerControllable::StaticClass()))
        {
            IPlayerControllable::Execute_MoveCustom(
                GetPawn(), Instance.GetValue().Get<FVector2D>());
        }
    }
}

void ALBPlayerController::PawnLook(const FInputActionInstance& Instance)
{
    if (Instance.GetValue().GetValueType() == EInputActionValueType::Axis2D)
    {
        if (GetPawn()->GetClass()->ImplementsInterface(
                UPlayerControllable::StaticClass()))
        {
            IPlayerControllable::Execute_LookCustom(
                GetPawn(), Instance.GetValue().Get<FVector2D>());
        }
    }
}

void ALBPlayerController::PawnJump(const FInputActionInstance& Instance)
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_JumpCustom(GetPawn());
    }
}

void ALBPlayerController::PawnSprint(const FInputActionInstance& Instance)
{
    if (Instance.GetValue().GetValueType() == EInputActionValueType::Boolean)
    {
        if (!GetPawn()) return;

        if (GetPawn()->GetClass()->ImplementsInterface(
                UPlayerControllable::StaticClass()))
        {
            IPlayerControllable::Execute_Sprint(
                GetPawn(), Instance.GetValue().Get<bool>());
        }
    }
}

void ALBPlayerController::PawnCrouch(const FInputActionInstance& Instance)
{
    if (Instance.GetValue().GetValueType() == EInputActionValueType::Boolean)
    {
        if (!GetPawn()) return;

        if (GetPawn()->GetClass()->ImplementsInterface(
                UPlayerControllable::StaticClass()))
        {
            IPlayerControllable::Execute_Crouch(
                GetPawn(), Instance.GetValue().Get<bool>());
        }
    }
}

void ALBPlayerController::PawnWalk(const FInputActionInstance& Instance)
{
    if (Instance.GetValue().GetValueType() == EInputActionValueType::Boolean)
    {
        if (!GetPawn()) return;

        if (GetPawn()->GetClass()->ImplementsInterface(
                UPlayerControllable::StaticClass()))
        {
            IPlayerControllable::Execute_Walk(
                GetPawn(), Instance.GetValue().Get<bool>());
        }
    }
}

void ALBPlayerController::PawnAim(const FInputActionInstance& Instance)
{
    if (Instance.GetValue().GetValueType() == EInputActionValueType::Boolean)
    {
        if (!GetPawn()) return;

        if (GetPawn()->GetClass()->ImplementsInterface(
                UPlayerControllable::StaticClass()))
        {
            IPlayerControllable::Execute_Aim(
                GetPawn(), Instance.GetValue().Get<bool>());
        }
    }
}

void ALBPlayerController::PawnPickUp(const FInputActionInstance& Instance)
{
    if (!GetPawn()) return;

    if (GetPawn()->GetClass()->ImplementsInterface(
            UPlayerControllable::StaticClass()))
    {
        IPlayerControllable::Execute_PickUp(GetPawn());
    }
}