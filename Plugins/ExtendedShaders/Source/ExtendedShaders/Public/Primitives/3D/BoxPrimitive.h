// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "BoxPrimitive.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(meta = (DisplayName = "Box", Category = "3D Primitives",
           ToolTip = "Draws a 3D box usign ray marching"))
class EXTENDEDSHADERS_API UBoxPrimitive : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UBoxPrimitive(const FObjectInitializer& ObjInit);

    // Inputs: bIsWorldSpace, WorldPosition, ObjectPosition
    // CameraVector, StepSize, NumRaySteps, CenterPosition,
    // Dimensions, Rotation, BevelRadius,
    // OverlapDetectionThreshold Color, LightDirection, AmbientLight,
    // ShadowContrast, RimStrength, RimContrast, RimColor, SpecularSoftness,
    // SpecularColor

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
