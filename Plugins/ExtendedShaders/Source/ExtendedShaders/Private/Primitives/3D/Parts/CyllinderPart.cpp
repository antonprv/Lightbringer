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

<<<<<<< Updated upstream
    // Inputs: WorldPosition, ObjectPosition, CameraVector
    // Location, Rotation, Scale,
    // HalfHeight, BevelRadius, Radius
    == == == =
                 // Inputs:  WorldPosition, ObjectPosition, CameraVector
                 //          Location, Rotation, Scale,
                 //          HalfHeight, BevelRadius, Radius

        // Outputs: OutWorldPosition, OutObjectPosition, OutCameraVector
        //          OutHalfHeight, OutBevelRadius, OutRadius
        //          OutLocation, OutRotation, OutScale

        // All inputs are just passed further and exist for convenience
>>>>>>> Stashed changes

        NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);
    NodeInputs.Add("CameraVector", &CameraVector);

    NodeInputs.Add("Location", &Location);
    NodeInputs.Add("Rotation", &Rotation);
    NodeInputs.Add("Scale", &Scale);

    NodeInputs.Add("Radius", &Radius);
    NodeInputs.Add("HalfHeight", &HalfHeight);
    NodeInputs.Add("BevelRadius", &BevelRadius);

    NodeOutputType = CMOT_Float1;
<<<<<<< Updated upstream
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Parts/CyllinderPart.hlsl");
    == == == =

                 FirstOutputName = "Part type";

    NodeAdditionalOutputs.Add("OutWorldPosition", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutObjectPosition", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutCameraVector", CMOT_Float3);

    NodeAdditionalOutputs.Add("OutRadius", CMOT_Float1);
    NodeAdditionalOutputs.Add("OutBevelRadius", CMOT_Float1);
    NodeAdditionalOutputs.Add("OutHalfHeight", CMOT_Float1);

    NodeAdditionalOutputs.Add("OutLocation", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutRotation", CMOT_Float3);
    NodeAdditionalOutputs.Add("OutScale", CMOT_Float3);

    UpdateNodeOutputs();

    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Parts/CyllinderPart.hlsl");
    HLSLIncludes.Add("/Libraries/Shapes/3D/Estimators/CyllinderEstimator.ush");
>>>>>>> Stashed changes
}