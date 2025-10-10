// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "LoadingCircleAnim.generated.h"

/**
 * Smoothly moves black and white mask left to right with no gradient.
 * Simple testing.
 */

class FMaterialCompiler;

UCLASS(meta = (DisplayName = "Loading Circle", Category = "Animations",
           Tooltip = "Windows-style circle loading animation."))
class EXTENDEDSHADERS_API ULoadingCircleAnim : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    ULoadingCircleAnim(const FObjectInitializer& ObjInit);

    // inputs: NumSides, NumRepeats, bIs3DMovement, Time, Speed, Center,
    // Radius, UV, Size

    UPROPERTY()
    FExpressionInput NumSides;

    UPROPERTY()
    FExpressionInput NumRepeats;

    UPROPERTY()
    FExpressionInput Is3DMovement;

    UPROPERTY()
    FExpressionInput Time;

    UPROPERTY()
    FExpressionInput Speed;

    UPROPERTY()
    FExpressionInput Center;

    UPROPERTY()
    FExpressionInput Radius;

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput Size;
};
