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

    int32 DefaultScaling{100};
    void SetScreenScaling(const EScreenScalingPreset& ScreenPercentage);
    void SetDefaultScalability();
    void SetLowScalability();
};
