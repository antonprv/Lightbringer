// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "DrawBricks.generated.h"

class FMaterialCompiler;

UCLASS(meta = (DisplayName = "Draw Bricks", Category = "Shapes",
           ToolTip = "Generates a tileable brick wall."))
class EXTENDEDSHADERS_API UDrawBricks : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UDrawBricks(const FObjectInitializer& ObjInit);

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput Tiling;

    UPROPERTY()
    FExpressionInput Offset;

    UPROPERTY()
    FExpressionInput Dimension;
};
