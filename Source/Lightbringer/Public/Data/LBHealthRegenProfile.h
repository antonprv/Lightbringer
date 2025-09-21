// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Curves/CurveFloat.h"
#include "LBHealthRegenProfile.generated.h"

/**
 * Health regen profile serves to split different health regen presets for
 * basic enemies \ bosses \ main character
 */
UCLASS()
class LIGHTBRINGER_API ULBHealthRegenProfile : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regen",
        meta = (Tooltip = "Delay before regen starts after taking damage"))
    float DelayAfterDamage{3.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regen",
        meta = (Tooltip =
                    "Base regen amount per second. Used if no curve is provided"))
    float RegenPerSecond{5.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regen",
        meta = (Tooltip = "Interval between regen ticks"))
    float RegenInterval{1.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regen",
        meta = (ClampMin = 0.f, ClampMax = 1.f,
            Tooltip =
                "Minimal health percentage to allow regen [0..1]. Example: 0.2 = only if > 20%"))
    float MinHealthPercentToRegen{0.1f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regen",
        meta = (Tooltip =
                    "Optional curve for nonlinear regen. X = time since regen start [sec], Y= regen per second"))
    UCurveFloat* RegenCurve = nullptr;
};
