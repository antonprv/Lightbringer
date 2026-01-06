// Copyright Anton Piruev. All Rights Reserved.
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
    Experimental
};

UENUM()
enum class EScreenScalingPreset : int32
{
    Partial = 75,
    Full = 100,
    Double = 200,
};

/**
 * Singleton-like class for managiing graphics presets
 */
UCLASS()
class LIGHTBRINGER_API UGraphicsPresetManager : public UObject
{
    GENERATED_BODY()

public:
    static UGraphicsPresetManager* Get();

    UFUNCTION(BlueprintCallable)
    void ApplyQualitySettings(const EGameGraphicsPreset& Preset);

    UFUNCTION(BlueprintCallable)
    void ApplyLowQualitySettings();

    UFUNCTION(BlueprintCallable)
    void ApplyDefaultQualitySettings();

    UFUNCTION(BlueprintCallable)
    void ApplyExperimentalQualitySettings();

    UFUNCTION(BlueprintCallable)
    bool IsAtLowQuality() const
    {
        return CurrentPreset == EGameGraphicsPreset::Low;
    }

private:
    bool bIsUsingTemporalAA{false};

    EGameGraphicsPreset CurrentPreset = EGameGraphicsPreset::Default;

    FTimerHandle VRAMCheckTimerHandle;

    int32 DefaultScaling{100};

    int32 PoolSize;

    int32 TotalVRAM;
    int32 UsedVRAM;
    int32 FreeVRAM;

    // start at 55% of VRAM for streaming
    float DefaultStreamingPoolPercentage{0.55f};
    float StreamingPoolPercentage{0.55f};
    float MinComfortableVRAM{1536.0f};

    void StartVRAMTrackingTask(const float& TickTime);
    void UpdateVRAMUsage();
    void AdjustStreamingPool();

    void SetScreenScaling(const EScreenScalingPreset& ScreenPercentage);
    void SetExperimentalScalability();
    void SetDefaultScalability();
    void SetLowScalability();
    void ApplyOptimizations();

    void AddAntiAliasing();

    void SetMSAASamples(const int& Quality);
    
    static constexpr float RareVRAMChecking = 15.f;
    static constexpr float OftenVRAMChecking = 5.f;
};
