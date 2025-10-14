// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "CyllinderPart.h"

UCyllinderPart::UCyllinderPart(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Cyllinder Part";
    FriendlyCategory = "3D Primitives";
    FriendlyDescription =
        "Cyllinder 3D Part, add RenderOperation to view it, add/intersect/subtract for boolean modelling";
    SetCategoryAndDescription();

    // Inputs: WorldPosition, ObjectPosition, CameraVector
    // Location, Rotation, Scale,
    // HalfHeight, BevelRadius, Radius

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);
    NodeInputs.Add("CameraVector", &CameraVector);

    NodeInputs.Add("CameraVector", &Location);
    NodeInputs.Add("StepSize", &Rotation);
    NodeInputs.Add("NumRaySteps", &Scale);

    NodeInputs.Add("HalfHeight", &HalfHeight);
    NodeInputs.Add("BevelRadius", &BevelRadius);
    NodeInputs.Add("Radius", &Radius);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Parts/CyllinderPart.hlsl");
}