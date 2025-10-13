// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "CyllinderPrimitive.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(meta = (DisplayName = "Cyllinder", Category = "3D Primitives",
           ToolTip = "Draws a 3D cyllinder usign ray marching"))
class EXTENDEDSHADERS_API UCyllinderPrimitive : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UCyllinderPrimitive(const FObjectInitializer& ObjInit);

    // Inputs: WorldPosition, ObjectPosition
    // CameraVector, StepSize, NumRaySteps, CenterPosition,
    // Location, Rotation, Transform,
    // HalfHeight, BevelRadius, Rotation
    // OverlapDetectionThreshold
    // Color, LightDirection, AmbientLight, ShadowContrast,
    // RimStrength, RimContrast, RimColor,
    // SpecularSoftness, SpecularColor

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
    FExpressionInput HalfHeight;
    UPROPERTY()
    FExpressionInput BevelRadius;

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
