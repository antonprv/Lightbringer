// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ULBHealthRegenProfile;
class ULBActorDamageParams;

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIGHTBRINGER_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        meta = (ClampMin = "0", ClampMax = "100", DisplayName = "Health"),
        Category = "Health Parameters")
    float MaxHealth{100.f};

    UFUNCTION(BlueprintCallable, Category = "Health Parameters",
        meta = (Tooltip = "One-time heal for n health"))
    void Heal(float Amount);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Parameters",
        DisplayName = "Auto Heal")
    bool bCanRegenerateHealth{true};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Parameters",
        meta = (EditCondition = "bCanRegenerateHealth"))
    ULBHealthRegenProfile* HealthRegenProfile{nullptr};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
    ULBActorDamageParams* ActorDamageParams{nullptr};

    UFUNCTION(BlueprintCallable, Category = "Damage Parameters",
        meta = (Tooltip = "Fall damage function"))
    virtual void TakeFallDamage(float JumpVelocity, const FHitResult& Hit);

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() { return CurrentHealth; };
    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetMaxHealth() const { return MaxHealth; }

    bool IsDead()
    {
        return FMath::IsNearlyZero(CurrentHealth) ||
               FMath::IsNegativeFloat(CurrentHealth);
    };

    bool IsAtFullHealth()
    {
        return FMath::IsNearlyEqual(CurrentHealth, MaxHealth);
    }

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

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

    void SetCurrentHealth(float Value);
};