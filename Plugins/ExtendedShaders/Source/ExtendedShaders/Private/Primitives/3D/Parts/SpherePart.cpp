// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "SpherePart.h"

USpherePart::USpherePart(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    FriendlyName = "Sphere Part";
    FriendlyCategory = "3D Primitives";
    FriendlyDescription =
        "Sphere 3D Part, add RenderOperation to view it, add/intersect/subtract for boolean modelling";
    SetCategoryAndDescription();

    NodeOutputType = CMOT_Float1;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Primitives/3D/Parts/SpherePart.hlsl");
}
