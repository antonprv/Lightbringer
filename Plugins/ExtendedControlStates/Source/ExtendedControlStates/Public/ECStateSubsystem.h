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

UENUM()
enum class ESpectatingState : uint8
{
    Spectating,
    Playing,
    Default
};

class UWorld;
class ASpectatorPawn;
class AController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnRespawnRequestSignature, AController*, Controller);

UCLASS()
class EXTENDEDCONTROLSTATES_API UECStateSubsystem
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UECStateSubsystem* Get(UWorld* World);

    // Control state fields
    UFUNCTION(BlueprintCallable, BlueprintPure,
        Category = "Extended Controller States")
    bool IsSpectating()
    {
        return CurrentState == ESpectatingState::Spectating;
    }

    UFUNCTION(BlueprintCallable, BlueprintPure,
        Category = "Extended Controller States")
    bool IsPlaying() { return CurrentState == ESpectatingState::Playing; }

    // Control state functions
    UFUNCTION(BlueprintCallable, Category = "Extended Controller States")
    void BeginSpectating(AController* Controller,
        TSubclassOf<ASpectatorPawn> SpectatorPawnClass);

    UFUNCTION(BlueprintCallable, Category = "Extended Controller States")
    void RespawnInWorld(AController* Controller);

    // Call to GameMode
    FOnRespawnRequestSignature OnRespawnRequest;

private:
    ASpectatorPawn* CustomSpectatorPawn;

    ESpectatingState CurrentState{ESpectatingState::Default};
};
