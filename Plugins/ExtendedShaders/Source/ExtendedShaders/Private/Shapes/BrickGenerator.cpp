// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "BrickGenerator.h"

#include "Materials/MaterialExpressionCustom.h"

UBrickGenerator::UBrickGenerator(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Brick Generator";
    FriendlyCategory = "Shapes";
    FriendlyDescription = "Generates a tileable brick wall.";
    SetCategoryAndDescription();

    NodeInputs.Add("Coord", &Coord);
    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("IsSoft", &IsSoft);
    NodeInputs.Add("Size", &Size);

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Shapes/BrickGenerator.hlsl");
}
