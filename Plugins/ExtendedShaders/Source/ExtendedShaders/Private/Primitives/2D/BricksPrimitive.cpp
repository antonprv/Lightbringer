// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "BricksPrimitive.h"

UBricksPrimitive::UBricksPrimitive(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Bricks";
    FriendlyCategory = "2D Primitives";
    FriendlyDescription = "Generates a tileable brick wall.";
    SetCategoryAndDescription();

    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("Tiling", &Tiling);
    NodeInputs.Add("Offset", &Offset);
    NodeInputs.Add("Dimension", &Dimension);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/2D/BricksPrimitive.hlsl");
}
