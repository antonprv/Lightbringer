// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "SimpleInputSubsystem.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

USimpleInputSubsystem* USimpleInputSubsystem::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<USimpleInputSubsystem>();
    }

    return nullptr;
}

void USimpleInputSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    InputManager = UInputManager::Get();
}

void USimpleInputSubsystem::Deinitialize()
{
    if (InputManager)
    {
        InputManager->RemoveFromRoot();
        InputManager = nullptr;
    }
    Super::Deinitialize();
}