// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "HealthComponentCore.h"
#include "HealthRegenProfile.h"

#include "GameFramework/DamageType.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogUHealthComponent, Log, Log)

UHealthComponentCore::UHealthComponentCore()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentHealth = MaxHealth;
}

// Called when the game starts
void UHealthComponentCore::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;

    AActor* Owner = GetOwner();

    if (Owner)
    {
        if (!Owner->OnTakeAnyDamage.Contains(this, FName("OnTakeAnyDamage")))
        {
            Owner->OnTakeAnyDamage.AddDynamic(
                this, &UHealthComponent::OnTakeAnyDamage);
        }
    }
}

void UHealthComponentCore::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
    const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (CurrentHealth <= 0 || IsDead()) return;
    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);

    if (IsDead())
    {
        StopRegen();
        OnDeath.Broadcast();
        return;
    }

    if (bCanRegenerateHealth)
    {
        StopRegen();
        if (HealthRegenProfile)
        {
            GetWorld()->GetTimerManager().SetTimer(RegenDelayHandle, this,
                &UHealthComponentCore::StartRegen,
                HealthRegenProfile->DelayAfterDamage, false);
        }
    }
}

void UHealthComponentCore::StartRegen()
{
    if (!HealthRegenProfile || CurrentHealth <= 0 || IsDead()) return;

    float MinHealth = MaxHealth * HealthRegenProfile->MinHealthPercentToRegen;
    if (CurrentHealth <= MinHealth) return;

    CurveTime = 0.f;
    GetWorld()->GetTimerManager().SetTimer(RegenTickHandle, this,
        &UHealthComponent::HandleRegen, HealthRegenProfile->RegenInterval,
        true);

    UE_LOG(LogUHealthComponent, Display,
        TEXT("Initialized health regeneration, current curve time: %d"),
        CurveTime);
}

void UHealthComponentCore::HandleRegen()
{
    if (!HealthRegenProfile || IsDead()) return;

    if (CurrentHealth <= 0.f)
    {
        StopRegen();
        return;
    }
    if (CurrentHealth >= MaxHealth)
    {
        StopRegen();
        return;
    }

    // Get value from a curve every n seconds
    CurveTime += HealthRegenProfile->RegenInterval;

    // Linear health regeneration or regeneration using a custom curve
    if (HealthRegenProfile->RegenCurve)
    {
        RegenRate = HealthRegenProfile->RegenCurve->GetFloatValue(CurveTime);
    }
    else if (!HealthRegenProfile->RegenCurve)
    {
        RegenRate = HealthRegenProfile->RegenPerSecond;
    }

    float HealAmount = RegenRate * HealthRegenProfile->RegenInterval;
    Heal(HealAmount);

    if (CurrentHealth >= MaxHealth) StopRegen();

    UE_LOG(LogUHealthComponent, Display,
        TEXT(
            "Regenerating health. Curve time untill regeneration completes: %f"),
        CurveTime);
}

void UHealthComponentCore::Heal(float Amount)
{
    if (CurrentHealth <= 0 || IsDead()) return;

    CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);
}

void UHealthComponentCore::StopRegen()
{
    GetWorld()->GetTimerManager().ClearTimer(RegenTickHandle);
    GetWorld()->GetTimerManager().ClearTimer(RegenDelayHandle);
    CurveTime = 0.f;

    UE_LOG(LogUHealthComponent, Display,
        TEXT("Stopped regenerating health. Set curve time to: %d"), CurveTime);
}
