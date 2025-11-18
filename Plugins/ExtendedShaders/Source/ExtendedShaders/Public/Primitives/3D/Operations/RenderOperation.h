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

    // Inputs:  Part
    //          WorldPosition, ObjectPosition
    //          CameraVector,
    //          Radius
    //          Location, Rotation, Scale
    //          StepSize, NumRaySteps,
    //          OverlapDetectionThreshold
    //          Color, LightDirection, AmbientLight, ShadowContrast,
    //          RimStrength, RimContrast, RimColor,
    //          SpecularSoftness, SpecularColor,
<<<<<<< Updated upstream
    == == == =
                 //          Radius, BevelRadius, HalfHeight
                 //          Location, Rotation, Scale
>>>>>>> Stashed changes

        UPROPERTY() FExpressionInput Part;

    UPROPERTY()
    FExpressionInput WorldPosition;
    UPROPERTY()
    FExpressionInput ObjectPosition;
    UPROPERTY()
    FExpressionInput CameraVector;

    UPROPERTY()
    FExpressionInput Radius;
<<<<<<< Updated upstream
    == == == = UPROPERTY() FExpressionInput BevelRadius;
    UPROPERTY()
    FExpressionInput HalfHeight;
>>>>>>> Stashed changes

    UPROPERTY()
    FExpressionInput Location;
    UPROPERTY()
    FExpressionInput Rotation;
    UPROPERTY()
    FExpressionInput Scale;

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
};
