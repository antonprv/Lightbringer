// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponentCore.generated.h"

class ULBHealthRegenProfile;

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HEALTHCOMPONENT_API UHealthComponentCore : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponentCore();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        meta = (ClampMin = "0", ClampMax = "100", DisplayName = "Health"),
        Category = "Health Parameters")
    float MaxHealth{100.f};

    UFUNCTION(BlueprintCallable, Category = "Health Parameters")
    void Heal(float Amount);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Parameters")
    bool bCanRegenerateHealth{true};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Parameters")
    ULBHealthRegenProfile* HealthRegenProfile{nullptr};

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() { return CurrentHealth; };
    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetMaxHealth() const { return MaxHealth; }

    bool IsDead() { return CurrentHealth <= 0; };

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage,
        const class UDamageType* DamageType, class AController* InstigatedBy,
        AActor* DamageCauser);

    UFUNCTION()
    void StartRegen();

    UFUNCTION()
    void HandleRegen();

private:
    float CurrentHealth{0.f};

    FTimerHandle RegenDelayHandle;
    FTimerHandle RegenTickHandle;

    float CurveTime{0.f};  // debug value to track curve behaviour
    float RegenRate{0.f};

    void StopRegen();
};
