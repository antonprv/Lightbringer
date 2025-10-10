// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "HologramConeAnim.generated.h"

/**
 *  Holographic-looking pseudo3D scifi shader.
 */

UCLASS(meta = (DisplayName = "Hologram Cone", Category = "Animations"))
class EXTENDEDSHADERS_API UHologramConeAnim : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UHologramConeAnim(const FObjectInitializer& ObjInit);

    // inputs: NumSides, NumRepeats, Time, Speed, Center, Radius, UV, Size,
    // ColorStart, ColorEnd, WhiteBrightness

    UPROPERTY()
    FExpressionInput NumSides;

    UPROPERTY()
    FExpressionInput NumRepeats;

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

    UPROPERTY()
    FExpressionInput ColorStart;

    UPROPERTY()
    FExpressionInput ColorEnd;

    UPROPERTY()
    FExpressionInput WhiteBrightness;
};
