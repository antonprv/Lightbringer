// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "DrawCircle.h"

UDrawCircle::UDrawCircle(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    FriendlyName = "Draw Circle";
    FriendlyCategory = "Shapes";
    FriendlyDescription =
        "Draws a circle, size and position value can be animated externally.";
    SetCategoryAndDescription();

    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("Tiling", &Tiling);
    NodeInputs.Add("Position", &Position);
    NodeInputs.Add("bIsSoft", &IsSoft);
    NodeInputs.Add("Size", &Size);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Shapes/DrawCircle.hlsl");
}