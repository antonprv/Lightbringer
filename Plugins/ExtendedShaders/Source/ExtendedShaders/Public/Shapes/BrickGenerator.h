// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "BrickGenerator.generated.h"

class FMaterialCompiler;

UCLASS(meta = (DisplayName = "Draw Bricks", Category = "Shapes",
           ToolTip = "Generates a tileable brick wall."))
class EXTENDEDSHADERS_API UBrickGenerator : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UBrickGenerator(const FObjectInitializer& ObjInit);

    UPROPERTY()
    FExpressionInput Coord;

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput IsSoft;

    UPROPERTY()
    FExpressionInput Size;

    UPROPERTY()
    FExpressionInput Dist;
};
