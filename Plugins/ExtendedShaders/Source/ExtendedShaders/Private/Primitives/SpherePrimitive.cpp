// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "SpherePrimitive.h"

USpherePrimitive::USpherePrimitive(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Sphere";
    FriendlyCategory = "Primitives";
    FriendlyDescription = "Draws a 3D sphere usign ray marching";
    SetCategoryAndDescription();

    // Inputs: bIsMaskedByGeometry, WorldPosition, ObjectPosition
    // CameraVector, NumRaySteps, Position, Radius, OverlapDetectionThreshold
    // Color

    NodeInputs.Add("bIsMaskedByGeometry", &IsMaskedByGeometry);

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);

    NodeInputs.Add("CameraVector", &CameraVector);
    NodeInputs.Add("NumRaySteps", &NumRaySteps);

    NodeInputs.Add("Position", &Position);
    NodeInputs.Add("Radius", &Radius);
    NodeInputs.Add("OverlapDetectionThreshold", &OverlapDetectionThreshold);
    NodeInputs.Add("Color", &Color);

    NodeOutputType = CMOT_Float4;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/SpherePrimitive.hlsl");
}
