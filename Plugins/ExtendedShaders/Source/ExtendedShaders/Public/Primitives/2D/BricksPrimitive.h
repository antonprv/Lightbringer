// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "BricksPrimitive.generated.h"

class FMaterialCompiler;

UCLASS(meta = (DisplayName = "Bricks", Category = "2D Primitives",
           ToolTip = "Generates a tileable brick wall."))
class EXTENDEDSHADERS_API UBricksPrimitive : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UBricksPrimitive(const FObjectInitializer& ObjInit);

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput Tiling;

    UPROPERTY()
    FExpressionInput Offset;

    UPROPERTY()
    FExpressionInput Dimension;
};
