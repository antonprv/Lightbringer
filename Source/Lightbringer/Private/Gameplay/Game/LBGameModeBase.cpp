// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBGameModeBase.h"
#include "LBPlayerCharacter.h"

ALBGameModeBase::ALBGameModeBase()
{
    DefaultPawnClass = ALBPlayerCharacter::StaticClass();
}
