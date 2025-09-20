// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "ECStateSubsystem.generated.h"

/**
 * This subsystem switches Controller states between possessing spectator and
 * possessing DefaultPawn (Spawning it from the PlayerStart)
 */

class UWorld;
class ASpectatorPawn;
class AController;

UCLASS()
class EXTENDEDCONTROLSTATES_API UECStateSubsystem
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UECStateSubsystem* Get(UWorld* World);

    UFUNCTION(BlueprintCallable, Category = "Extended Controller States")
    void BeginSpectating(
        AController* Controller, TSubclassOf<ASpectatorPawn> SpectatorPawn);

    UFUNCTION(BlueprintCallable, Category = "Extended Controller States")
    void RespawnInWorld(AGameModeBase* GameMode, AController* Controller);

private:
    ASpectatorPawn* SpectatorPawn;
};
