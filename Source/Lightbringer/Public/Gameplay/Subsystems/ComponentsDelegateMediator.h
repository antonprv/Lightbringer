// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ComponentsDelegateMediator.generated.h"

/**
 * Serves as "event bus" between different actor components, while also
 * bridging view logic and gameplay logic
 */

class AActor;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorDeathSignature, AActor*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(
    FOnJumpDamageSignature, AActor*, float, const FHitResult&);

UCLASS()
class LIGHTBRINGER_API UComponentsDelegateMediator
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UComponentsDelegateMediator* Get(UWorld* World);

    void DispatchPlayerJumpDamage(
        AActor* DamagedActor, float Velocity, const FHitResult& HitResult);

    void DispatchActorDeath(AActor* DeadActor);

    FOnJumpDamageSignature OnJumpDamage;
    FOnActorDeathSignature OnActorDeath;
};
