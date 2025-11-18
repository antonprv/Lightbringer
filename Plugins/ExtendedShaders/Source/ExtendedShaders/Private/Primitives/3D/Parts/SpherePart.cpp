// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Primitives/3D/Parts/SpherePart.h"

USpherePart::USpherePart(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    FriendlyName = "Sphere Part";
    FriendlyCategory = "3D Primitives";
    FriendlyDescription =
        "Sphere 3D Part, add RenderOperation to view it, add/intersect/subtract for boolean modelling";
    SetCategoryAndDescription();

    // Inputs:  WorldPosition, ObjectPosition, CameraVector
    //          Radius
    //          Location, Rotation, Scale

    // Outputs  OutWorldPosition, OutObjectPosition, OutCameraVector
    //          Part
    //          OutLocation, OutRotation, OutScale
    //          OutRadius

    // All inputs are just passed further and exist for convenience

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);
    NodeInputs.Add("CameraVector", &CameraVector);

    NodeInputs.Add("Radius", &Radius);

    NodeInputs.Add("Location", &Location);
    NodeInputs.Add("Rotation", &Rotation);
    NodeInputs.Add("Scale", &Scale);

    NodeOutputType = CMOT_Float1;
    FirstOutputName = "Part type";

    NodeAdditionalOutputs.Add("OutWorldPosition", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutObjectPosition", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutCameraVector", CMOT_Float3);

    NodeAdditionalOutputs.Add("OutRadius", CMOT_Float1);

    NodeAdditionalOutputs.Add("OutLocation", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutRotation", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutScale", CMOT_Float3);

    UpdateNodeOutputs();

    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Parts/SpherePart.hlsl");
    HLSLIncludes.Add("/Libraries/Shapes/3D/Estimators/SphereEstimator.ush");
}