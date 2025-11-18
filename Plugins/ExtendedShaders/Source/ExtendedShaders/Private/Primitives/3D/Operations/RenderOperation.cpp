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

    // Inputs:  Part
    //          WorldPosition, ObjectPosition
    //          CameraVector,
    //          Radius
    //          Location, Rotation, Scale
    //          StepSize, NumRaySteps,
    //          OverlapDetectionThreshold
    //          Color, LightDirection, AmbientLight, ShadowContrast,
    //          RimStrength, RimContrast, RimColor,
    //          SpecularSoftness, SpecularColor,
<<<<<<< Updated upstream
    == == == =
                 //          Radius, BevelRadius, HalfHeight
                 //          Location, Rotation, Scale
>>>>>>> Stashed changes

        NodeInputs.Add("Part", &Part);

    NodeInputs.Add("WorldPosition", &WorldPosition);
    NodeInputs.Add("ObjectPosition", &ObjectPosition);
    NodeInputs.Add("CameraVector", &CameraVector);

    NodeInputs.Add("Radius", &Radius);
<<<<<<< Updated upstream

    == == == = NodeInputs.Add("BevelRadius", &BevelRadius);
    NodeInputs.Add("HalfHeight", &HalfHeight);
    
>>>>>>> Stashed changes
    NodeInputs.Add("Location", &Location);
    NodeInputs.Add("Rotation", &Rotation);
    NodeInputs.Add("Scale", &Scale);

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

    NodeOutputType = CMOT_Float4;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Operations/RenderOperation.hlsl");
    HLSLIncludes.Add("/Libraries/Shapes/3D/Operands/RenderOperand.ush");
}
