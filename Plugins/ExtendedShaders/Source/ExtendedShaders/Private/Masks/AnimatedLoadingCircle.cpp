// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "AnimatedLoadingCircle.h"

UAnimatedLoadingCircle::UAnimatedLoadingCircle(
    const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Animated Loading Circle";
    FriendlyCategory = "Masks";
    FriendlyDescription = "Windows-style circle loading animation.";
    SetCategoryAndDescription();

    NodeInputs.Add("NumSides", &NumSides);
    NodeInputs.Add("Center", &CenterPosition);
    NodeInputs.Add("Radius", &Radius);
    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("Size", &Size);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Masks/AnimLoadingCircle.hlsl");
}