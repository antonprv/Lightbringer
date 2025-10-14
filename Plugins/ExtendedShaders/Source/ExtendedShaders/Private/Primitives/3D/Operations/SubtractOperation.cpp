// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "SubtractOperation.h"

USubtractOperation::USubtractOperation(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Subtract Operation";
    FriendlyCategory = "3D Primitives Operations";
    FriendlyDescription =
        "Performs a boolean subtraction on any two 3D Parts given.";
    SetCategoryAndDescription();

    // Inputs:WorldPosition, ObjectPosition
    // CameraVector
    // Location, Rotation, Scale
    // BevelRadius, ChamferRadius, DetectionRadius
    // ShapeA, ShapeB

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);
    NodeInputs.Add("CameraVector", &CameraVector);

    NodeInputs.Add("Location", &Location);
    NodeInputs.Add("Rotation", &Rotation);
    NodeInputs.Add("Scale", &Scale);

    NodeInputs.Add("BevelRadius", &BevelRadius);
    NodeInputs.Add("ChamferRadius", &ChamferRadius);
    NodeInputs.Add("DetectionRadius", &DetectionRadius);

    NodeInputs.Add("ShapeA", &ShapeA);
    NodeInputs.Add("ShapeB", &ShapeB);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Operations/SubtractOperation.hlsl");
}
