// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "GraphicsPresetManager.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/GameUserSettings.h"

UGraphicsPresetManager* UGraphicsPresetManager::Get()
{
    static TWeakObjectPtr<UGraphicsPresetManager> Instance;

    if (!Instance.IsValid())
    {
        Instance = NewObject<UGraphicsPresetManager>(GetTransientPackage());
        Instance->AddToRoot();  // prevent GC if you want it alive for whole
                                // runtime
    }

    return Instance.Get();
}

void UGraphicsPresetManager::ApplyQualitySettings(
    const EGameGraphicsPreset& Preset)
{
    switch (Preset)
    {
        case EGameGraphicsPreset::Low:
        {
            SetLowScalability();
            SetScreenScaling(EScreenScalingPreset::Half);
            CurrentPreset = EGameGraphicsPreset::Low;
            break;
        }
        case EGameGraphicsPreset::Default:
        {
            SetDefaultScalability();
            SetScreenScaling(EScreenScalingPreset::Full);
            CurrentPreset = EGameGraphicsPreset::Default;
            break;
        }
        default: break;
    }
}

void UGraphicsPresetManager::SetScreenScaling(
    const EScreenScalingPreset& ScreenPercentage)
{
    if (GEngine && GEngine->GameViewport)
    {
        // Set the screen percentage (resolution fraction) via console variable
        FString Command =
            FString::Printf(TEXT("r.ScreenPercentage %d"), ScreenPercentage);
        GEngine->GameViewport->Exec(nullptr, *Command, *GLog);
    }
}

void UGraphicsPresetManager::SetDefaultScalability()
{
    if (GEngine)
    {
        if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
        {
            Settings->ScalabilityQuality.AntiAliasingQuality = 0;
            Settings->ScalabilityQuality.EffectsQuality = 0;
            Settings->ScalabilityQuality.PostProcessQuality = 1;
            Settings->ScalabilityQuality.ShadowQuality = 0;
            Settings->ScalabilityQuality.TextureQuality = 0;
            Settings->ScalabilityQuality.ViewDistanceQuality = 1;

            // Apply and save the settings
            Settings->ApplyNonResolutionSettings();
            Settings->ConfirmVideoMode();
            Settings->ApplySettings(false);
            Settings->SaveSettings();
        }
    }
}

void UGraphicsPresetManager::SetLowScalability()
{
    if (GEngine)
    {
        if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
        {
            // Set all scalability settings to low (0)
            Settings->ScalabilityQuality.AntiAliasingQuality = 0;
            Settings->ScalabilityQuality.EffectsQuality = 0;
            Settings->ScalabilityQuality.PostProcessQuality = 0;
            Settings->ScalabilityQuality.ShadowQuality = 0;
            Settings->ScalabilityQuality.TextureQuality = 0;
            Settings->ScalabilityQuality.ViewDistanceQuality = 0;

            // Apply and save the settings
            Settings->ApplyNonResolutionSettings();
            Settings->ConfirmVideoMode();
            Settings->ApplySettings(false);
            Settings->SaveSettings();
        }
    }
}