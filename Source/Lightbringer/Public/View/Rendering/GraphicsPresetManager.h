// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphicsPresetManager.generated.h"

UENUM()
enum class EGameGraphicsPreset : uint8
{
    Low,
    Default,
};

UENUM()
enum class EScreenScalingPreset : int32
{
    Half = 50,
    Full = 100,
};

/**
 * Singleton-like class for managiing graphics presets
 */
UCLASS()
class UGraphicsPresetManager : public UObject
{
    GENERATED_BODY()

public:
    static UGraphicsPresetManager* Get();

    void ApplyQualitySettings(const EGameGraphicsPreset& Preset);
    void ApplyLowQualitySettings()
    {
        return ApplyQualitySettings(EGameGraphicsPreset::Low);
    };
    void ApplyDefaultQualitySettings()
    {
        return ApplyQualitySettings(EGameGraphicsPreset::Default);
    };

    UFUNCTION(BlueprintCallable)
    bool IsAtLowQuality() const
    {
        return CurrentPreset == EGameGraphicsPreset::Low;
    }

private:
    EGameGraphicsPreset CurrentPreset = EGameGraphicsPreset::Default;

    FTimerHandle VRAMCheckTimerHandle;

    int32 DefaultScaling{100};

    int32 PoolSize;
    // start at 55% of VRAM for streaming
    float DefaultStreamingPoolPercentage{0.55f};
    float StreamingPoolPercentage{0.55f};
    float MinComfortableVRAM{1536.0f};

    void StartVRAMTrackingTask(const float& TickTime);
    void UpdateVRAMUsage();
    void AdjustStreamingPool();

    void SetScreenScaling(const EScreenScalingPreset& ScreenPercentage);
    void SetDefaultScalability();
    void SetLowScalability();
    void ApplyOptimizations();

    static constexpr float RareVRAMChecking = 15.f;
    static constexpr float OftenVRAMChecking = 5.f;
};
