// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "LoadPixel.generated.h"

/**
 * Signed Distant Field Sphere, rendered using raymarching
 */
UCLASS(meta = (DisplayName = "Load Pixel", Category = "Image Editing | Utils",
           ToolTip = "Loads selected pixel"))
class EXTENDEDSHADERS_API ULoadPixel : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    ULoadPixel(const FObjectInitializer& ObjInit);

    // Inputs:  InTexture2D, Index
    // Outputs: LoadedPixel2D

    UPROPERTY()
    FExpressionInput InTexture2D;
    UPROPERTY()
    FExpressionInput Index;
};
