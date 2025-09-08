// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#include "Public/Subsystems/QualitySettingsSubsystem.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Rendering/Presets/GraphicsPresetManager.h"

UQualitySettingsSubsystem* UQualitySettingsSubsystem::Get()
{
    if (!GEngine || !GEngine->GetWorld())
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(GEngine->GetWorld()))
    {
        return GI->GetSubsystem<UQualitySettingsSubsystem>();
    }

    return nullptr;
}

void UQualitySettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
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