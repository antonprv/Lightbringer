// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Rendering/GraphicsPresetManager.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/GameUserSettings.h"
#include "HAL/IConsoleManager.h"

#include "GPUCheck/Public/GPUCheck.h"

DEFINE_LOG_CATEGORY_STATIC(LogUGraphicsPresetManager, Log, Log)

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
            break;
        }
        case EGameGraphicsPreset::Default:
        {
            SetDefaultScalability();
            break;
        }
        case EGameGraphicsPreset::Experimental:
        {
            SetExperimentalScalability();
            break;
        }
        default: break;
    }

    ApplyOptimizations();
    CurrentPreset = Preset;
}

void UGraphicsPresetManager::ApplyLowQualitySettings()
{
    return ApplyQualitySettings(EGameGraphicsPreset::Low);
}

void UGraphicsPresetManager::ApplyDefaultQualitySettings()
{
    return ApplyQualitySettings(EGameGraphicsPreset::Default);
}

void UGraphicsPresetManager::ApplyExperimentalQualitySettings()
{
    return ApplyQualitySettings(EGameGraphicsPreset::Experimental);
}

void UGraphicsPresetManager::StartVRAMTrackingTask(const float& TickTime)
{
    if (GEngine && GEngine->GetWorld())
    {
        GEngine->GetWorld()->GetTimerManager().ClearTimer(
            VRAMCheckTimerHandle);

        GEngine->GetWorld()->GetTimerManager().SetTimer(VRAMCheckTimerHandle,
            this, &UGraphicsPresetManager::UpdateVRAMUsage, TickTime, true);
    }
}

void UGraphicsPresetManager::UpdateVRAMUsage()
{
    TotalVRAM = FGPUCheckModule::GetTotalVRAM();
    UsedVRAM = FGPUCheckModule::GetUsedVRAM();

    if (TotalVRAM <= 0) return;  // fallback is handled in GPUCheckModule

    // Calculate free VRAM
    FreeVRAM = TotalVRAM - UsedVRAM;

    // If free VRAM drops below threshold, reduce pool percentage
    if (FreeVRAM < MinComfortableVRAM)
    {
        StreamingPoolPercentage = FMath::Clamp(StreamingPoolPercentage - 0.05f,
            0.3f, DefaultStreamingPoolPercentage);
        AdjustStreamingPool();
    }
    else if (FreeVRAM > MinComfortableVRAM * 2 &&
             StreamingPoolPercentage < 1.0f)
    {
        // Gradually restore pool if enough VRAM
        StreamingPoolPercentage = FMath::Clamp(StreamingPoolPercentage + 0.02f,
            0.3f, DefaultStreamingPoolPercentage);
        AdjustStreamingPool();
    }
}

void UGraphicsPresetManager::AdjustStreamingPool()
{
    PoolSize = FGPUCheckModule::GetTotalVRAM() * StreamingPoolPercentage;

    // Set pool
    static IConsoleVariable* CVarPoolSize =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.Streaming.PoolSize"));
    if (CVarPoolSize)
    {
        CVarPoolSize->Set(PoolSize);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.Streaming.PoolSize = %d"), PoolSize)
    }
}

void UGraphicsPresetManager::SetScreenScaling(
    const EScreenScalingPreset& ScreenPercentage)
{
    if (GEngine && GEngine->GameViewport)
    {
        // Set the screen percentage (resolution fraction) via console variable
        static IConsoleVariable* CVarScreenPercentage =
            IConsoleManager::Get().FindConsoleVariable(
                TEXT("r.ScreenPercentage"));
        if (CVarScreenPercentage)
        {
            CVarScreenPercentage->Set(static_cast<int32>(ScreenPercentage));
            UE_LOG(LogUGraphicsPresetManager, Display,
                TEXT("Set CVar: r.ScreenPercentage = %d"),
                static_cast<int32>(ScreenPercentage))
        }
    }

    if (!bIsUsingTemporalAA) return;

    static IConsoleVariable* CVarTemporalAAScreen =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.TemporalAA.HistoryScreenPercentage"));
    if (CVarTemporalAAScreen)
    {
        CVarTemporalAAScreen->Set(static_cast<int32>(ScreenPercentage));
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.TemporalAA.HistoryScreenPercentage = %d"),
            static_cast<int32>(ScreenPercentage))
    }
}

void UGraphicsPresetManager::SetExperimentalScalability()
{
    if (GEngine)
    {
        if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
        {
            Settings->ScalabilityQuality.AntiAliasingQuality = 3;
            Settings->ScalabilityQuality.EffectsQuality = 0;
            Settings->ScalabilityQuality.PostProcessQuality = 1;
            Settings->ScalabilityQuality.ShadowQuality = 0;
            Settings->ScalabilityQuality.TextureQuality = 1;
            Settings->ScalabilityQuality.ViewDistanceQuality = 1;

            // Apply and save the settings
            Settings->ApplyNonResolutionSettings();
            Settings->ConfirmVideoMode();
            Settings->ApplySettings(false);
            Settings->SaveSettings();
        }

        // If we select this, we probably have a powerful GPU
        // so this is more like an emergency check.
        StartVRAMTrackingTask(RareVRAMChecking);

        SetScreenScaling(EScreenScalingPreset::Double);

        AddAntiAliasing();
        SetMSAASamples(8);

        static IConsoleVariable* CVarBloom =
            IConsoleManager::Get().FindConsoleVariable(
                TEXT("r.DefaultFeature.Bloom"));
        if (CVarBloom)
        {
            CVarBloom->Set(1);
            UE_LOG(LogUGraphicsPresetManager, Display,
                TEXT("Set CVar: r.DefaultFeature.Bloom = %d"), 1)
        }
    }
}

void UGraphicsPresetManager::SetDefaultScalability()
{
    if (GEngine)
    {
        if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
        {
            Settings->ScalabilityQuality.AntiAliasingQuality = 2;
            Settings->ScalabilityQuality.EffectsQuality = 0;
            Settings->ScalabilityQuality.PostProcessQuality = 1;
            Settings->ScalabilityQuality.ShadowQuality = 0;
            Settings->ScalabilityQuality.TextureQuality = 0;
            Settings->ScalabilityQuality.ViewDistanceQuality = 0;

            // Apply and save the settings
            Settings->ApplyNonResolutionSettings();
            Settings->ConfirmVideoMode();
            Settings->ApplySettings(false);
            Settings->SaveSettings();
        }

        // If we select this, we probably have a powerful GPU
        // so this is more like an emergency check.
        StartVRAMTrackingTask(RareVRAMChecking);

        SetScreenScaling(EScreenScalingPreset::Full);

        AddAntiAliasing();
        SetMSAASamples(4);
    }
}

void UGraphicsPresetManager::SetLowScalability()
{
    if (GEngine)
    {
        if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
        {
            // Set all scalability settings to low (0)
            Settings->ScalabilityQuality.AntiAliasingQuality = 1;
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

        // If we select this, we probably have a weak GPU,
        // so we periodically check for VRAM overflow.
        StartVRAMTrackingTask(OftenVRAMChecking);

        SetScreenScaling(EScreenScalingPreset::Partial);

        AddAntiAliasing();
        SetMSAASamples(2);
    }
}

void UGraphicsPresetManager::ApplyOptimizations()
{
    AdjustStreamingPool();

    static IConsoleVariable* CVarEarlyZPass =
        IConsoleManager::Get().FindConsoleVariable(TEXT("r.EarlyZPass"));
    if (CVarEarlyZPass)
    {
        CVarEarlyZPass->Set(2);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.EarlyZPass = %d"), 2)
    }

    static IConsoleVariable* CVarClearScreenMethod =
        IConsoleManager::Get().FindConsoleVariable(TEXT("r.ClearSceneMethod"));
    if (CVarClearScreenMethod)
    {
        CVarClearScreenMethod->Set(0);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.ClearSceneMethod = %d"), 0)
    }

    static IConsoleVariable* CVarFinishFrame =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.FinishCurrentFrame"));
    if (CVarFinishFrame)
    {
        CVarFinishFrame->Set(0);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.FinishCurrentFrame = %d"), 0)
    }

    static IConsoleVariable* CVarMaxCSM =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.Shadow.MaxCSMResolution"));
    if (CVarMaxCSM)
    {
        CVarMaxCSM->Set(512);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.Shadow.MaxCSMResolution = %d"), 512)
    }

    static IConsoleVariable* CVarMinShadow =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.Shadow.MinResolution"));
    if (CVarMinShadow)
    {
        CVarMinShadow->Set(32);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.Shadow.MinResolution = %d"), 32)
    }

    static IConsoleVariable* CVarBackgroundStream =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.Streaming.UseBackgroundThreadPool"));
    if (CVarBackgroundStream)
    {
        CVarBackgroundStream->Set(1);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.Streaming.UseBackgroundThreadPool = %d"), 1)
    }

    static IConsoleVariable* CVarLimitPool =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.Streaming.LimitPoolSizeToVRAM"));
    if (CVarLimitPool)
    {
        CVarLimitPool->Set(1);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.Streaming.LimitPoolSizeToVRAM = %d"), 1)
    }

    static IConsoleVariable* CVarAniso =
        IConsoleManager::Get().FindConsoleVariable(TEXT("r.MaxAnisotropy"));
    if (CVarAniso)
    {
        CVarAniso->Set(4);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.MaxAnisotropy = %d"), 4)
    }
}

void UGraphicsPresetManager::AddAntiAliasing()
{
    bIsUsingTemporalAA = true;

    static IConsoleVariable* CVarAAMethod =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.DefaultFeature.AntiAliasing"));
    if (CVarAAMethod)
    {
        CVarAAMethod->Set(2);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.DefaultFeature.AntiAliasing = %d"), 2)
    }
}

void UGraphicsPresetManager::SetMSAASamples(const int& Quality)
{
    static IConsoleVariable* CVarAASamples =
        IConsoleManager::Get().FindConsoleVariable(TEXT("r.TemporalAASamples"));
    if (CVarAASamples)
    {
        CVarAASamples->Set(Quality);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.TemporalAASamples = %d"), Quality)
    }
}