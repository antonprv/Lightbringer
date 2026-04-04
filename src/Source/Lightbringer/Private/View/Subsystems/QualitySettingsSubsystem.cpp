// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "QualitySettingsSubsystem.h"
#include "GraphicsPresetManager.h"

#include "Engine/Engine.h"
#include "Engine/World.h"

#include "Kismet/GameplayStatics.h"

UQualitySettingsSubsystem* UQualitySettingsSubsystem::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<UQualitySettingsSubsystem>();
    }

    return nullptr;
}

void UQualitySettingsSubsystem::Initialize(
    FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    Manager = UGraphicsPresetManager::Get();
}

void UQualitySettingsSubsystem::Deinitialize()
{
    if (Manager)
    {
        Manager->RemoveFromRoot();
        Manager = nullptr;
    }
    Super::Deinitialize();
}