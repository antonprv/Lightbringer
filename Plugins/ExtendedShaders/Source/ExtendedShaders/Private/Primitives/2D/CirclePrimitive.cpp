// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Primitives/2D/CirclePrimitive.h"

UCirclePrimitive::UCirclePrimitive(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Circle";
    FriendlyCategory = "2D Primitives";
    FriendlyDescription =
        "Draws a 2D Circle, size, position and tiling can be animated externally.";
    SetCategoryAndDescription();

    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("Tiling", &Tiling);
    NodeInputs.Add("Position", &Position);
    NodeInputs.Add("bIsSoft", &IsSoft);
    NodeInputs.Add("Size", &Size);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/2D/CirclePrimitive.hlsl");
}