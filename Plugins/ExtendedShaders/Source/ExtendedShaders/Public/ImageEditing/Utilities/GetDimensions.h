// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "GetDimensions.generated.h"

/**
 * Get distance
 */

class UMaterialExpressionTextureProperty;

UCLASS(
    meta = (DisplayName = "Get Dimensions", Category = "Image Editing | Utils",
        ToolTip = "Get real-world dimensions of an image"))
class EXTENDEDSHADERS_API UGetDimensions : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UGetDimensions(const FObjectInitializer& ObjInit);

    // Inputs:  InTexture2D
    // Outputs: Dimensions

    UPROPERTY()
    FExpressionInput InTexture2D;
};
