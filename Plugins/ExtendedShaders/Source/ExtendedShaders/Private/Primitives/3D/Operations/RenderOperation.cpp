// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "RenderOperation.h"

URenderOperation::URenderOperation(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Render Operation";
    FriendlyCategory = "3D Primitives Operations";
    FriendlyDescription =
        "Renders out individual 3D Parts or other operation's result";
    SetCategoryAndDescription();

    // Inputs:WorldPosition, ObjectPosition
    // CameraVector, StepSize, NumRaySteps,
    // OverlapDetectionThreshold
    // Color, LightDirection, AmbientLight, ShadowContrast,
    // RimStrength, RimContrast, RimColor,
    // SpecularSoftness, SpecularColor,
    // Part

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);

    NodeInputs.Add("CameraVector", &CameraVector);
    NodeInputs.Add("StepSize", &StepSize);
    NodeInputs.Add("NumRaySteps", &NumRaySteps);
    NodeInputs.Add("OverlapDetectionThreshold", &OverlapDetectionThreshold);

    NodeInputs.Add("Color", &Color);
    NodeInputs.Add("LightDirection", &LightDirection);
    NodeInputs.Add("AmbientLight", &AmbientLight);
    NodeInputs.Add("ShadowContrast", &ShadowContrast);

    NodeInputs.Add("RimStrength", &RimStrength);
    NodeInputs.Add("RimContrast", &RimContrast);
    NodeInputs.Add("RimColor", &RimColor);

    NodeInputs.Add("SpecularSoftness", &SpecularSoftness);
    NodeInputs.Add("SpecularColor", &SpecularColor);

    NodeInputs.Add("Part", &Part);

    NodeOutputType = CMOT_Float4;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Operations/RenderOperation.hlsl");
}
