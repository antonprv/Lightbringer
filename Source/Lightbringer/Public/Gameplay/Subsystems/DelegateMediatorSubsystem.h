// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DelegateMediatorSubsystem.generated.h"

class UWorld;
class APawn;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDeath, APawn*);

UCLASS()
class LIGHTBRINGER_API UDelegateMediatorSubsystem
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UDelegateMediatorSubsystem* Get(UWorld* World);

    void DispatchPlayerDeath(APawn* DeadPawn);

    FOnPlayerDeath OnPlayerDeath;
};
