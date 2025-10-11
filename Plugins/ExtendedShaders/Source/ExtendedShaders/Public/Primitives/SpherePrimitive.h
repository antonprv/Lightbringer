// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "SpherePrimitive.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(meta = (DisplayName = "Sphere", Category = "Primitives",
           ToolTip = "Draws a 3D sphere usign ray marching"))
class EXTENDEDSHADERS_API USpherePrimitive : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    USpherePrimitive(const FObjectInitializer& ObjInit);

    // Inputs: bIsMaskedByGeometry, WorldPosition, ObjectPosition
    // CameraVector, NumRaySteps, Position, Radius, OverlapDetectionThreshold
    // Color

    UPROPERTY()
    FExpressionInput IsMaskedByGeometry;

    UPROPERTY()
    FExpressionInput WorldPosition;

    UPROPERTY()
    FExpressionInput ObjectPosition;

    UPROPERTY()
    FExpressionInput CameraVector;

    UPROPERTY()
    FExpressionInput NumRaySteps;

    UPROPERTY()
    FExpressionInput Position;

    UPROPERTY()
    FExpressionInput Radius;

    UPROPERTY()
    FExpressionInput OverlapDetectionThreshold;

    UPROPERTY()
    FExpressionInput Color;
};
