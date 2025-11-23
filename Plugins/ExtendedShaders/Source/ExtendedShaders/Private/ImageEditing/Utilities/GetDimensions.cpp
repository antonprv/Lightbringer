// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "ImageEditing/Utilities/GetDimensions.h"
#include "Materials/MaterialExpressionTextureProperty.h"

UGetDimensions::UGetDimensions(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Get Dimensions";
    FriendlyCategory = "Image Editing | Utils";
    FriendlyDescription =
        "Get real-world dimensions of an image";
    SetCategoryAndDescription();

    // Inputs:  InTexture2D
    // Outputs: Dimensions

    NodeTypedInputs.Add("InTexture2D",
        FTypedInput(&InTexture2D, ENodeInputType::TextureObject));

    NodeOutputType = CMOT_Float2;

    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/ImageEditing/Utilities/GetDimensions.hlsl");
}
