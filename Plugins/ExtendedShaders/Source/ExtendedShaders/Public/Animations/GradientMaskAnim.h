// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "GradientMaskAnim.generated.h"

/**
 * Smoothly moves black and white mask left to right with no gradient.
 * Simple testing.
 */

class FMaterialCompiler;

UCLASS(
    meta = (DisplayName = "Gradient Mask", Category = "Animations",
        Tooltip =
            "Smoothly moves a black - and-white mask from left to right with no gradient."))
class EXTENDEDSHADERS_API UGradientMaskAnim : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UGradientMaskAnim(const FObjectInitializer& ObjInit);

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput Steps;

    UPROPERTY()
    FExpressionInput Time;

    UPROPERTY()
    FExpressionInput Speed;

    UPROPERTY()
    FExpressionInput IsGradient;
};
