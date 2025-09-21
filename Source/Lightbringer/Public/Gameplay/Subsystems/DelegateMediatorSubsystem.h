// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DelegateMediatorSubsystem.generated.h"

class UWorld;
class APawn;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDeathSignature, APawn*);
DECLARE_MULTICAST_DELEGATE_TwoParams(
    FOnJumpDamagSignature, float, const FHitResult&);

UCLASS()
class LIGHTBRINGER_API UDelegateMediatorSubsystem
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UDelegateMediatorSubsystem* Get(UWorld* World);

    void DispatchPlayerDeath(APawn* DeadPawn);
    void DispatchPlayerJumpDamage(float Velocity, const FHitResult& HitResult);

    FOnPlayerDeathSignature OnPlayerDeath;
    FOnJumpDamagSignature OnJumpDamage;
};
