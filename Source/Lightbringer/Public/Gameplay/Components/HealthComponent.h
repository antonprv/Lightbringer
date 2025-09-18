// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIGHTBRINGER_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        meta = (ClampMin = "0", ClampMax = "100", DisplayName = "Health"))
    float MaxHealth{100.f};

    float GetHealth() { return Health; };

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    float Health{0.f};
};
