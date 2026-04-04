// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Containers/ArrayView.h"
#include "HealthAggregatorSubsystem.generated.h"

/**
 * Goes over level and aggregates over all actors with Health component, tracks
 * health state, can be used for applying mass damage delegates, auras or for
 * testing
 */

class UHealthComponent;
class UWorld;

UCLASS()
class LIGHTBRINGER_API UHealthAggregatorSubsystem
    : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UHealthAggregatorSubsystem* Get(UWorld* World);

    void RegisterHealth(UHealthComponent* Component);
    void UnregisterHealth(UHealthComponent* Component);

    // Safe read-only access to all live health components
    TArrayView<UHealthComponent* const> GetAllHealthComponents() const;

protected:
    virtual void Deinitialize() override;

private:
    TArray<TWeakObjectPtr<UHealthComponent>> HealthComponents;

    // Buffer for TConstArrayView
    mutable TArray<UHealthComponent*> TempValidComponents;
};