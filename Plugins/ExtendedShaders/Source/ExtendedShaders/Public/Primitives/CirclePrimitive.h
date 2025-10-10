// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Utils/CustomHLSLExpression.h"
#include "CirclePrimitive.generated.h"

class FMaterialCompiler;

UCLASS(
    meta = (DisplayName = "Circle", Category = "Primitives",
        ToolTip =
            "Draws a circle, size and position value can be animated externally."))
class EXTENDEDSHADERS_API UCirclePrimitive : public UCustomHLSLExpression
{
    GENERATED_BODY()

public:
    UCirclePrimitive(const FObjectInitializer& ObjInit);

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput Tiling;

    UPROPERTY()
    FExpressionInput Position;

    UPROPERTY()
    FExpressionInput IsSoft;

    UPROPERTY()
    FExpressionInput Size;
};