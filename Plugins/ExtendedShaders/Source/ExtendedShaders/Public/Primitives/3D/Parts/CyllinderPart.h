// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "CyllinderPart.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(
    meta = (DisplayName = "Cyllinder Part", Category = "3D Primitives",
        ToolTip =
            "Cyllinder 3D Part, add RenderOperation to view it, add/intersect/subtract for boolean modelling"))
class EXTENDEDSHADERS_API UCyllinderPart : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UCyllinderPart(const FObjectInitializer& ObjInit);

    // Inputs:  WorldPosition, ObjectPosition, CameraVector
    //          Location, Rotation, Scale,
    //          HalfHeight, BevelRadius, Radius

    // Outputs: OutWorldPosition, OutObjectPosition, OutCameraVector
    //          OutHalfHeight, OutBevelRadius, OutRadius
    //          OutLocation, OutRotation, OutScale

    // All inputs are just passed further and exist for convenience

    UPROPERTY()
    FExpressionInput WorldPosition;
    UPROPERTY()
    FExpressionInput ObjectPosition;
    UPROPERTY()
    FExpressionInput CameraVector;

    UPROPERTY()
    FExpressionInput Location;
    UPROPERTY()
    FExpressionInput Rotation;
    UPROPERTY()
    FExpressionInput Scale;

    UPROPERTY()
    FExpressionInput Radius;
    UPROPERTY()
    FExpressionInput BevelRadius;
    UPROPERTY()
    FExpressionInput HalfHeight;
};
