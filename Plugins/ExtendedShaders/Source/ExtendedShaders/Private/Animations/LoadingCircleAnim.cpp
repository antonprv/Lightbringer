// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Animations/LoadingCircleAnim.h"

ULoadingCircleAnim::ULoadingCircleAnim(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Loading Circle";
    FriendlyCategory = "Animations";
    FriendlyDescription = "Windows-style circle loading animation.";
    SetCategoryAndDescription();

    // inputs: NumSides, NumRepeats, bIs3DMovement, Time, Speed, Center,
    // Radius, UV, Size

    NodeInputs.Add("NumSides", &NumSides);
    NodeInputs.Add("NumRepeats", &NumRepeats);
    NodeInputs.Add("bIs3DMovement", &Is3DMovement);
    NodeInputs.Add("Time", &Time);
    NodeInputs.Add("Speed", &Speed);
    NodeInputs.Add("Center", &Center);
    NodeInputs.Add("Radius", &Radius);
    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("Size", &Size);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Animations/LoadingCircleAnim.hlsl");
}