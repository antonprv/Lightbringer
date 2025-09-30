// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBGameModeBase.h"
#include "LBPlayerCharacter.h"
#include "LBPlayerController.h"
#include "LBSpectatorPawn.h"
#include "UI/LBHUD.h"

ALBGameModeBase::ALBGameModeBase()
{
    DefaultPawnClass = ALBPlayerCharacter::StaticClass();
    PlayerControllerClass = ALBPlayerController::StaticClass();
    SpectatorClass = ALBSpectatorPawn::StaticClass();
    HUDClass = ALBHUD::StaticClass();
}
