// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Gameplay/Components/HealthComponent.h"

#include "GameFramework/DamageType.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Engine/DamageEvents.h"

#include "Data/LBHealthRegenProfile.h"
#include "Data/LBActorDamageParams.h"
#include "View/Player/LBPlayerCharacter.h"
#include "Gameplay/Subsystems/ComponentsDelegateMediator.h"

DEFINE_LOG_CATEGORY_STATIC(LogUHealthComponent, Log, Log)

void UHealthComponent::SetCurrentHealth(float Value)
{
    const float NewHealth = FMath::Clamp(Value, 0.f, MaxHealth);
    if (FMath::IsNearlyEqual(CachedHealth, NewHealth, 0.5f)) return;

    CachedHealth = NewHealth;
    CurrentHealth = NewHealth;
    OnHealthChanged.Broadcast(CurrentHealth);
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
    if (AActor* Owner = GetOwner())
    {
        if (Owner->OnTakeAnyDamage.Contains(this,
                GET_FUNCTION_NAME_CHECKED(UHealthComponent, OnTakeAnyDamage)))
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

        ComponentsDelegateMediator->DispatchActorDeath(GetOwner());

        return;
    }

    if (bCanRegenerateHealth && HealthRegenProfile &&
        !RegenTickHandle.IsValid())
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
        TEXT("Initialized health regeneration, current curve time: %f"),
        CurveTime);
}

void UHealthComponent::HandleRegen()
{
    if (IsDead() || IsAtFullHealth())
    {
        StopRegen();
        return;
    }

    // Предварительный расчет значений кривой при инициализации профиля
    const float RegenValue =
        HealthRegenProfile->RegenCurve
            ? HealthRegenProfile->GetCachedRegenValue(CurveTime)
            : HealthRegenProfile->RegenPerSecond;

    CurveTime += HealthRegenProfile->RegenInterval;
    const float HealAmount = RegenValue * HealthRegenProfile->RegenInterval;

    if (HealAmount > 0) SetCurrentHealth(CurrentHealth + HealAmount);
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
        TEXT("Stopped regenerating health. Set curve time to: %f"), CurveTime);
}