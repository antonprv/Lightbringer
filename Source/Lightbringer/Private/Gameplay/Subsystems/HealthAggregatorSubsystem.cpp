// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "HealthAggregatorSubsystem.h"
#include "Components/HealthComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

UHealthAggregatorSubsystem* UHealthAggregatorSubsystem::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<UHealthAggregatorSubsystem>();
    }

    return nullptr;
}

void UHealthAggregatorSubsystem::Deinitialize()
{
    HealthComponents.Empty();
    TempValidComponents.Empty();
    Super::Deinitialize();
}

void UHealthAggregatorSubsystem::RegisterHealth(UHealthComponent* Component)
{
    if (!Component) return;
    HealthComponents.AddUnique(Component);
}

void UHealthAggregatorSubsystem::UnregisterHealth(UHealthComponent* Component)
{
    if (!Component) return;
    HealthComponents.Remove(Component);
}

TArrayView<UHealthComponent* const> UHealthAggregatorSubsystem::
    GetAllHealthComponents() const
{
    TempValidComponents.Reset();
    for (TWeakObjectPtr<UHealthComponent> WeakComp : HealthComponents)
    {
        if (UHealthComponent* Comp = WeakComp.Get())
        {
            TempValidComponents.Add(Comp);
        }
    }
    return TArrayView<UHealthComponent* const>(TempValidComponents);
}
