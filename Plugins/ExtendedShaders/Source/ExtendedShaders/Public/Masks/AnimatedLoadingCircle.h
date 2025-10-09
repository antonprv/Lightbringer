// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "AnimatedLoadingCircle.generated.h"

/**
 * Smoothly moves black and white mask left to right with no gradient.
 * Simple testing.
 */

class FMaterialCompiler;

UCLASS(meta = (DisplayName = "Animated Loading Circle", Category = "Masks",
           Tooltip = "Windows-style circle loading animation."))
class EXTENDEDSHADERS_API UAnimatedLoadingCircle : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UAnimatedLoadingCircle(const FObjectInitializer& ObjInit);

    // inputs: n_sides, center, radius, uv, size

    UPROPERTY()
    FExpressionInput NumSides;

    UPROPERTY()
    FExpressionInput CenterPosition;

    UPROPERTY()
    FExpressionInput Radius;

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput Size;
};
