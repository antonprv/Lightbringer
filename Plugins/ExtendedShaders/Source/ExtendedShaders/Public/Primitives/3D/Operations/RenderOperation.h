// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "RenderOperation.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(meta = (DisplayName = "Render Operation",
           Category = "3D Primitives Operations",
           ToolTip =
               "Renders out individual 3D Parts or other operation's result"))
class EXTENDEDSHADERS_API URenderOperation : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    URenderOperation(const FObjectInitializer& ObjInit);

    // Inputs:WorldPosition, ObjectPosition
    // CameraVector, StepSize, NumRaySteps,
    // OverlapDetectionThreshold
    // Color, LightDirection, AmbientLight, ShadowContrast,
    // RimStrength, RimContrast, RimColor,
    // SpecularSoftness, SpecularColor,
    // Part

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

    UPROPERTY()
    FExpressionInput Part;
};
