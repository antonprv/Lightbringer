// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Gameplay/Game/LBGameModeBase.h"

#include "View/UI/LBHUD.h"

#include "View/Player/LBPlayerCharacter.h"
#include "View/Player/LBPlayerController.h"
#include "View/Player/LBSpectatorPawn.h"
#include "GameFramework/Controller.h"

#include "ECStateSubsystem.h"

ALBGameModeBase::ALBGameModeBase()
{
    DefaultPawnClass = ALBPlayerCharacter::StaticClass();
    PlayerControllerClass = ALBPlayerController::StaticClass();
    HUDClass = ALBHUD::StaticClass();
}

void ALBGameModeBase::StartPlay()
{
    Super::StartPlay();

    if (UECStateSubsystem* ControllerState =
            UECStateSubsystem::Get(GetWorld()))
    {
        if (!ControllerState->OnRespawnRequest.Contains(
                this, GET_FUNCTION_NAME_CHECKED(
                          ALBGameModeBase, HandleRespawnRequest)))
        {
            ControllerState->OnRespawnRequest.AddDynamic(
                this, &ALBGameModeBase::HandleRespawnRequest);
        }
    }
}

void ALBGameModeBase::StartToLeaveMap() 
{
    if (UECStateSubsystem* ControllerState =
            UECStateSubsystem::Get(GetWorld()))
    {
        if (ControllerState->OnRespawnRequest.Contains(
                this, GET_FUNCTION_NAME_CHECKED(
                          ALBGameModeBase, HandleRespawnRequest)))
        {
            ControllerState->OnRespawnRequest.RemoveDynamic(
                this, &ALBGameModeBase::HandleRespawnRequest);
        }
    }
}

void ALBGameModeBase::HandleRespawnRequest(AController* Controller)
{
    RestartPlayer(Controller);
}
