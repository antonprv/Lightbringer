// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "HealthComponent.h"
#include "HealthComponentAggregator.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

UHealthComponentAggregator* UHealthComponentAggregator::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<UHealthComponentAggregator>();
    }

    return nullptr;
}

void UHealthComponentAggregator::Deinitialize()
{
    HealthComponents.Empty();
    TempValidComponents.Empty();
    Super::Deinitialize();
}

void UHealthComponentAggregator::RegisterHealth(UHealthComponent* Component)
{
    if (!Component) return;
    HealthComponents.AddUnique(Component);
}

void UHealthComponentAggregator::UnregisterHealth(UHealthComponent* Component)
{
    if (!Component) return;
    HealthComponents.Remove(Component);
}

TArrayView<UHealthComponent* const> UHealthComponentAggregator::
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
