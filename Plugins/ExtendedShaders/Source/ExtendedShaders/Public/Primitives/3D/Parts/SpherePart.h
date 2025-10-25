// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "SpherePart.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(
    meta = (DisplayName = "Sphere Part", Category = "3D Primitives",
        ToolTip =
            "Sphere 3D Part, add RenderOperation to view it, add/intersect/subtract for boolean modelling"))
class EXTENDEDSHADERS_API USpherePart : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    USpherePart(const FObjectInitializer& ObjInit);

    // Inputs:  WorldPosition, ObjectPosition, CameraVector
    //          Radius
    //          Location, Rotation, Scale

    // Outputs  OutWorldPosition, OutObjectPosition, OutCameraVector
    //          OutRadius
    //          OutLocation, OutRotation, OutScale
    //          Part

    UPROPERTY()
    FExpressionInput WorldPosition;
    UPROPERTY()
    FExpressionInput ObjectPosition;
    UPROPERTY()
    FExpressionInput CameraVector;

    UPROPERTY()
    FExpressionInput Radius;

    UPROPERTY()
    FExpressionInput Location;
    UPROPERTY()
    FExpressionInput Rotation;
    UPROPERTY()
    FExpressionInput Scale;
};
