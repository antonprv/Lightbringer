// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "SpherePrimitive.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(meta = (DisplayName = "Sphere", Category = "3D Primitives",
           ToolTip = "Draws a 3D sphere usign ray marching"))
class EXTENDEDSHADERS_API USpherePrimitive : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    USpherePrimitive(const FObjectInitializer& ObjInit);

    // Inputs: WorldPosition, ObjectPosition
    // CameraVector, StepSize, NumRaySteps, CenterPosition, Radius,
    // OverlapDetectionThreshold Color, LightDirection, AmbientLight,
    // ShadowContrast, RimStrength, RimContrast, RimColor, SpecularSoftness,
    // SpecularColor, Location, Rotation, Scale

    UPROPERTY()
    FExpressionInput WorldPosition;
    UPROPERTY()
    FExpressionInput ObjectPosition;
    UPROPERTY()
    FExpressionInput CameraVector;
    UPROPERTY()
    FExpressionInput StepSize;
    UPROPERTY()
    FExpressionInput NumRaySteps;
    UPROPERTY()
    FExpressionInput OverlapDetectionThreshold;

    UPROPERTY()
    FExpressionInput Location;
    UPROPERTY()
    FExpressionInput Rotation;
    UPROPERTY()
    FExpressionInput Scale;

    UPROPERTY()
    FExpressionInput Radius;

    UPROPERTY()
    FExpressionInput Color;

    UPROPERTY()
    FExpressionInput LightDirection;
    UPROPERTY()
    FExpressionInput AmbientLight;
    UPROPERTY()
    FExpressionInput ShadowContrast;
    UPROPERTY()
    FExpressionInput RimStrength;
    UPROPERTY()
    FExpressionInput RimContrast;
    UPROPERTY()
    FExpressionInput RimColor;
    UPROPERTY()
    FExpressionInput SpecularSoftness;
    UPROPERTY()
    FExpressionInput SpecularColor;
};
