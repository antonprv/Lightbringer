// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Gameplay/Game/LBGameModeBase.h"

#include "View/UI/LBHUD.h"

#include "View/Player/LBPlayerCharacter.h"
#include "View/Player/LBPlayerController.h"
#include "View/Player/LBSpectatorPawn.h"

ALBGameModeBase::ALBGameModeBase()
{
    DefaultPawnClass = ALBPlayerCharacter::StaticClass();
    PlayerControllerClass = ALBPlayerController::StaticClass();
    SpectatorClass = ALBSpectatorPawn::StaticClass();
    HUDClass = ALBHUD::StaticClass();
}
