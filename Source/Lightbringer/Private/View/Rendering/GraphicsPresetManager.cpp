// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Rendering/GraphicsPresetManager.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/GameUserSettings.h"

#include "GPUCheck/Public/GPUCheckModule.h"

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
            SetScreenScaling(EScreenScalingPreset::Half);
            break;
        }
        case EGameGraphicsPreset::Default:
        {
            SetDefaultScalability();
            SetScreenScaling(EScreenScalingPreset::Full);
            break;
        }
        default: break;
    }

    ApplyOptimizations();
    CurrentPreset = Preset;
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
    int32 TotalVRAM = FGPUCheckModule::GetTotalVRAM();
    int32 UsedVRAM = FGPUCheckModule::GetUsedVRAM();

    if (TotalVRAM <= 0) return;  // fallback is handled in GPUCheckModule

    // Calculate free VRAM
    int32 FreeVRAM = TotalVRAM - UsedVRAM;

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
                TEXT("Set CVar: r.ScreenPercentage = %d"), ScreenPercentage)
        }
    }
}

void UGraphicsPresetManager::SetDefaultScalability()
{
    if (GEngine)
    {
        if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
        {
            Settings->ScalabilityQuality.AntiAliasingQuality = 3;
            Settings->ScalabilityQuality.EffectsQuality = 1;
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

        // If we select this, we probably have a powerful GPU
        // so this is more like an emergency check.
        StartVRAMTrackingTask(RareVRAMChecking);

        AddAntiAliasing();
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
            Settings->ScalabilityQuality.EffectsQuality = 1;
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

        RemoveAntiAliasing();
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

    static IConsoleVariable* CVarShadowParallelCull =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.Shadow.ParallelCull"));
    if (CVarShadowParallelCull)
    {
        CVarShadowParallelCull->Set(0);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.Shadow.ParallelCull = %d"), 0)
    }
}

void UGraphicsPresetManager::AddAntiAliasing() 
{
    static IConsoleVariable* CVarMSAACount =
        IConsoleManager::Get().FindConsoleVariable(
            TEXT("r.MSAACount"));
    if (CVarMSAACount)
    {
        CVarMSAACount->Set(4);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.MSAACount = %d"), 4)
    }
}

void UGraphicsPresetManager::RemoveAntiAliasing() 
{
    static IConsoleVariable* CVarMSAACount =
        IConsoleManager::Get().FindConsoleVariable(TEXT("r.MSAACount"));
    if (CVarMSAACount)
    {
        CVarMSAACount->Set(0);
        UE_LOG(LogUGraphicsPresetManager, Display,
            TEXT("Set CVar: r.MSAACount = %d"), 0)
    }
}
