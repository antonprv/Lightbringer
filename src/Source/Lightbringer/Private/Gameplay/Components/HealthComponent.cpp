// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Components/HealthComponent.h"
#include "LBHealthRegenProfile.h"
#include "LBActorDamageParams.h"
#include "LBPlayerCharacter.h"

#include "GameFramework/DamageType.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "ComponentsDelegateMediator.h"

DEFINE_LOG_CATEGORY_STATIC(LogUHealthComponent, Log, Log)

void UHealthComponent::SetCurrentHealth(float Value)
{
    CurrentHealth = FMath::Clamp(Value, 0.f, MaxHealth);
}

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetCurrentHealth(MaxHealth);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    ComponentsDelegateMediator = UComponentsDelegateMediator::Get(GetWorld());

    check(ComponentsDelegateMediator);

    SetCurrentHealth(MaxHealth);

    if (AActor* Owner = GetOwner())
    {
        if (!Owner->OnTakeAnyDamage.Contains(this, FName("OnTakeAnyDamage")))
        {
            Owner->OnTakeAnyDamage.AddDynamic(
                this, &UHealthComponent::OnTakeAnyDamage);
        }

        if (!ComponentsDelegateMediator->OnJumpDamage.IsBoundToObject(this))
        {
            ComponentsDelegateMediator->OnJumpDamage.AddUObject(
                this, &UHealthComponent::TakeFallDamage);
        }
    }
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UComponentsDelegateMediator* DelegateMediator =
            UComponentsDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->OnJumpDamage.RemoveAll(this);
    }

    if (AActor* Owner = GetOwner())
    {
        if (Owner->OnTakeAnyDamage.Contains(this, FName("OnTakeAnyDamage")))
        {
            Owner->OnTakeAnyDamage.RemoveDynamic(
                this, &UHealthComponent::OnTakeAnyDamage);
        }
    }

    if (ComponentsDelegateMediator->OnJumpDamage.IsBoundToObject(this))
    {
        ComponentsDelegateMediator->OnJumpDamage.RemoveAll(this);
    }

    Super::EndPlay(EndPlayReason);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
    const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (!GetWorld() || IsDead()) return;
    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);

    if (IsDead())
    {
        StopRegen();

        if (ComponentsDelegateMediator)
        {
            ComponentsDelegateMediator->DispatchActorDeath(GetOwner());
        }

        return;
    }

    if (bCanRegenerateHealth)
    {
        StopRegen();
        if (HealthRegenProfile)
        {
            GetWorld()->GetTimerManager().SetTimer(RegenDelayHandle, this,
                &UHealthComponent::StartRegen,
                HealthRegenProfile->DelayAfterDamage, false);
        }
    }
}

void UHealthComponent::TakeFallDamage(
    AActor* DamagedActor, float JumpVelocity, const FHitResult& Hit)
{
    if (!ActorDamageParams || !GetOwner() || GetOwner() != DamagedActor ||
        JumpVelocity < ActorDamageParams->FallVelocityBounds.X)
        return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = Hit;

    float Damage = FMath::GetMappedRangeValueClamped(
        ActorDamageParams->FallVelocityBounds,
        ActorDamageParams->FallVelocityDamage, JumpVelocity);

    GetOwner()->TakeDamage(Damage, PointDamageEvent, nullptr, nullptr);

    UE_LOG(LogUHealthComponent, Display,
        TEXT("Took fall damage on %f velocity: %f"), JumpVelocity, Damage);
}

void UHealthComponent::StartRegen()
{
    if (!HealthRegenProfile || IsDead() || IsAtFullHealth()) return;

    float MinHealth = MaxHealth * HealthRegenProfile->MinHealthPercentToRegen;

    if (FMath::IsNearlyEqual(CurrentHealth, MinHealth)) return;

    CurveTime = 0.f;
    GetWorld()->GetTimerManager().SetTimer(RegenTickHandle, this,
        &UHealthComponent::HandleRegen, HealthRegenProfile->RegenInterval,
        true);

    UE_LOG(LogUHealthComponent, Display,
        TEXT("Initialized health regeneration, current curve time: %d"),
        CurveTime);
}

void UHealthComponent::HandleRegen()
{
    if (!HealthRegenProfile) return;

    if (IsDead())
    {
        StopRegen();
        return;
    }

    if (IsAtFullHealth())
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

    if (IsAtFullHealth() || IsDead())
    {
        StopRegen();
    }

    UE_LOG(LogUHealthComponent, Display,
        TEXT(
            "Regenerating health. Curve time untill regeneration completes: %f"),
        CurveTime);
}

void UHealthComponent::Heal(float Amount)
{
    if (IsDead()) return;

    SetCurrentHealth(CurrentHealth + Amount);
    OnHealthChanged.Broadcast(CurrentHealth);
}

void UHealthComponent::StopRegen()
{
    GetWorld()->GetTimerManager().ClearTimer(RegenTickHandle);
    GetWorld()->GetTimerManager().ClearTimer(RegenDelayHandle);
    CurveTime = 0.f;

    UE_LOG(LogUHealthComponent, Display,
        TEXT("Stopped regenerating health. Set curve time to: %d"), CurveTime);
}