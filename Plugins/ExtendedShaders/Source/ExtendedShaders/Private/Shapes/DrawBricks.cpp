// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "DrawBricks.h"

UDrawBricks::UDrawBricks(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    FriendlyName = "Draw Bricks";
    FriendlyCategory = "Shapes";
    FriendlyDescription = "Generates a tileable brick wall.";
    SetCategoryAndDescription();

    NodeInputs.Add("uv", &UV);
    NodeInputs.Add("tiling", &Tiling);
    NodeInputs.Add("offset", &Offset);
    NodeInputs.Add("dimension", &Dimension);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Shapes/DrawBricks.hlsl");
}
