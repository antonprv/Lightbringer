// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestGameMode.h"
#include "TestPawn.h"

ATestGameMode::ATestGameMode()
{
    DefaultPawnClass = ATestPawn::StaticClass();
}
