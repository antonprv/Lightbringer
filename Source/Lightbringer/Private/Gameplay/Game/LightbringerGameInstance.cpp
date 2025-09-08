// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#include "Gameplay/Game/LightbringerGameInstance.h"
#include "Gameplay/Subsystems/QualitySettingsSubsystem.h"

void ULightbringerGameInstance::OnStart()
{
    Super::OnStart();

    UQualitySettingsSubsystem* QualitySettingsSubsystem = UQualitySettingsSubsystem::Get();
    // Example: set low graphics settings at startup
    QualitySettingsSubsystem->GetManager()->ApplyLowQualitySettings();
}

void ULightbringerGameInstance::Shutdown()
{
    Super::Shutdown();
}