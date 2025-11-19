// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LBGameModeBase.generated.h"

/**
 *
 */

class AController;

UCLASS()
class LIGHTBRINGER_API ALBGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ALBGameModeBase();

protected:
    virtual void StartPlay() override;

    virtual void StartToLeaveMap() override;

private:
    UFUNCTION()
    void HandleRespawnRequest(AController* Controller);
};
