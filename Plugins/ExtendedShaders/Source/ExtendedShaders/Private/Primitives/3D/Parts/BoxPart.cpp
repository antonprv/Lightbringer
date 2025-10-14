// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "BoxPart.h"

UBoxPart::UBoxPart(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    FriendlyName = "Box Part";
    FriendlyCategory = "3D Primitives";
    FriendlyDescription =
        "Box 3D Part, add RenderOperation to view it, add/intersect/subtract for boolean modelling";
    SetCategoryAndDescription();

    // Inputs:WorldPosition, ObjectPosition, CameraVector
    // Location, Rotation, Scale
    // BevelRadius

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);
    NodeInputs.Add("CameraVector", &CameraVector);

    NodeInputs.Add("Location", &Location);
    NodeInputs.Add("Rotation", &Rotation);
    NodeInputs.Add("Scale", &Scale);

    NodeInputs.Add("BevelRadius", &BevelRadius);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Parts/BoxPart.hlsl");
}
