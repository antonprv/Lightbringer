// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Dev/TestBasic/TestGameMode.h"
#include "Dev/TestBasic/TestPawn.h"
#include "Dev/TestBasic/TestPlayerController.h"

ATestGameMode::ATestGameMode()
{
    DefaultPawnClass = ATestPawn::StaticClass();

    PlayerControllerClass = ATestPlayerController::StaticClass();
}
