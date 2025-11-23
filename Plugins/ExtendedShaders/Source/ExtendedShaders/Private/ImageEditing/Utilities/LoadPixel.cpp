// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "ImageEditing/Utilities/LoadPixel.h"

ULoadPixel::ULoadPixel(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    FriendlyName = "Load Pixel";
    FriendlyCategory = "Image Editing | Utils";
    FriendlyDescription = "Loads selected pixel";
    SetCategoryAndDescription();

    // Inputs:  InTexture2D, Index
    // Outputs: LoadedPixel2D

    NodeInputs.Add("InTexture2D", &InTexture2D);
    NodeInputs.Add("Index", &Index);

    NodeOutputType = CMOT_Float2;

    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/ImageEditing/Utilities/LoadPixel.hlsl");
}
