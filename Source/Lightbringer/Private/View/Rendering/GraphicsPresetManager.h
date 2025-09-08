// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphicsPresetManager.generated.h"

UENUM()
enum class EGraphicsPreset : uint8
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

    void ApplyQualitySettings(const EGraphicsPreset& Preset);
    void ApplyLowQualitySettings() 
    {
        return ApplyQualitySettings(EGraphicsPreset::Low);
    };
    void ApplyDefaultQualitySettings()
    {
        return ApplyQualitySettings(EGraphicsPreset::Default);
    };

    UFUNCTION(BlueprintCallable)
    bool IsAtLowQuality() const { return CurrentPreset == EGraphicsPreset::Low; }

private:
    EGraphicsPreset CurrentPreset = EGraphicsPreset::Default;

    int32 DefaultScaling{100};
    void SetScreenScaling(const EScreenScalingPreset& ScreenPercentage);
    void SetDefaultScalability();
    void SetLowScalability();
    void SetMaxFPS(const int32& MaxFPS);
};
