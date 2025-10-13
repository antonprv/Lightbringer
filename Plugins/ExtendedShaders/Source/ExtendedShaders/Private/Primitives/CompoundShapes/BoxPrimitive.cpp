// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "BoxPrimitive.h"

UBoxPrimitive::UBoxPrimitive(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Box";
    FriendlyCategory = "3D Primitives";
    FriendlyDescription = "Draws a 3D box usign ray marching";
    SetCategoryAndDescription();

    // Inputs: bIsWorldSpace, WorldPosition, ObjectPosition
    // CameraVector, StepSize, NumRaySteps, CenterPosition,
    // Dimensions, Rotation, BevelRadius,
    // OverlapDetectionThreshold Color, LightDirection, AmbientLight,
    // ShadowContrast, RimStrength, RimContrast, RimColor, SpecularSoftness,
    // SpecularColor

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);

    NodeInputs.Add("CameraVector", &CameraVector);
    NodeInputs.Add("StepSize", &StepSize);
    NodeInputs.Add("NumRaySteps", &NumRaySteps);
    NodeInputs.Add("OverlapDetectionThreshold", &OverlapDetectionThreshold);

    NodeInputs.Add("Location", &Location);
    NodeInputs.Add("Rotation", &Rotation);
    NodeInputs.Add("Scale", &Scale);

    NodeInputs.Add("BevelRadius", &BevelRadius);

    NodeInputs.Add("Color", &Color);

    NodeInputs.Add("LightDirection", &LightDirection);
    NodeInputs.Add("AmbientLight", &AmbientLight);
    NodeInputs.Add("ShadowContrast", &ShadowContrast);

    NodeInputs.Add("RimStrength", &RimStrength);
    NodeInputs.Add("RimContrast", &RimContrast);
    NodeInputs.Add("RimColor", &RimColor);

    NodeInputs.Add("SpecularSoftness", &SpecularSoftness);
    NodeInputs.Add("SpecularColor", &SpecularColor);

    NodeOutputType = CMOT_Float4;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/BoxPrimitive.hlsl");
}
