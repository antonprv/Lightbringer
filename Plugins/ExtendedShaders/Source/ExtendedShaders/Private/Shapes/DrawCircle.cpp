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

    NodeInputs.Add("uv", &UV);
    NodeInputs.Add("tiling", &Tiling);
    NodeInputs.Add("position", &Position);
    NodeInputs.Add("is_soft", &IsSoft);
    NodeInputs.Add("size", &Size);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Shapes/DrawCircle.hlsl");
}