// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerDelegateMediator.generated.h"

class UWorld;
class APawn;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDestructionSignature, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDeathSignature, APawn*);

UCLASS()
class LIGHTBRINGER_API UPlayerDelegateMediator : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UPlayerDelegateMediator* Get(UWorld* World);

    void DispatchPlayerDestruction(AActor* PlayerActor);
    void DispatchPlayerDeath(APawn* DeadPawn);

    FOnPlayerDestructionSignature OnPlayerDestruction;
    FOnPlayerDeathSignature OnPlayerDeath;
};
