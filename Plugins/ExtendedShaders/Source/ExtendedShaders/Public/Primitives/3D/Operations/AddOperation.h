// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "AddOperation.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(meta = (DisplayName = "Add Operation",
           Category = "3D Primitives Operations",
           ToolTip = "Performs a boolean addition on any two 3D Parts given."))
class EXTENDEDSHADERS_API UAddOperation : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UAddOperation(const FObjectInitializer& ObjInit);

    // Inputs:WorldPosition, ObjectPosition
    // CameraVector
    // Location, Rotation, Scale
    // BevelRadius, ChamferRadius, DetectionRadius
    // ShapeA, ShapeB

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
    FExpressionInput BevelRadius;
    UPROPERTY()
    FExpressionInput ChamferRadius;
    UPROPERTY()
    FExpressionInput DetectionRadius;

    UPROPERTY()
    FExpressionInput ShapeA;
    UPROPERTY()
    FExpressionInput ShapeB;
};
