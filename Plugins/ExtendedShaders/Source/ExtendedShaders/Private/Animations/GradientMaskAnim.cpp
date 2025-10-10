// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "GradientMaskAnim.h"

UGradientMaskAnim::UGradientMaskAnim(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Gradient Mask";
    FriendlyCategory = "Animations";
    FriendlyDescription =
        "Smoothly moves a black - and-white mask from left to right with no gradient.";
    SetCategoryAndDescription();

    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("Steps", &Steps);
    NodeInputs.Add("Time", &Time);
    NodeInputs.Add("Speed", &Speed);
    NodeInputs.Add("bIsGradient", &IsGradient);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Animations/GradientMaskAnim.hlsl");
}