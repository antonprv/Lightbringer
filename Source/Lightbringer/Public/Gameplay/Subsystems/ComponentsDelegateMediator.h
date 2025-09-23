// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ComponentsDelegateMediator.generated.h"

/**
 * Effectively an event bus between Player View and gameplay logic
 */

DECLARE_MULTICAST_DELEGATE_TwoParams(
    FOnJumpDamageSignature, float, const FHitResult&);

UCLASS()
class LIGHTBRINGER_API UComponentsDelegateMediator
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UComponentsDelegateMediator* Get(UWorld* World);

    void DispatchPlayerJumpDamage(float Velocity, const FHitResult& HitResult);

    FOnJumpDamageSignature OnJumpDamage;
};
