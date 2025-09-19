// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Components/HealthComponent.h"

#include "GameFramework/DamageType.h"

#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogUHealthComponent, Log, Log)

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

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

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
    const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (Health <= 0 || IsDead()) return;
    Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}