// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "DrawCircle.generated.h"

class FMaterialCompiler;

UCLASS(
    meta = (DisplayName = "Draw Circle", Category = "Shapes",
        ToolTip =
            "Draws a circle, size and position value can be animated externally."))
class LIGHTBRINGER_API UDrawCircle : public UMaterialExpression
{
    GENERATED_BODY()

public:
    UDrawCircle();

    UPROPERTY()
    FExpressionInput UV;

    UPROPERTY()
    FExpressionInput Position;

    UPROPERTY()
    FExpressionInput Size;

    UPROPERTY()
    FExpressionInput Tiling;

    UPROPERTY()
    FExpressionInput Softness;

    UPROPERTY()
    FExpressionInput NoSoftness;

protected:
#if WITH_EDITOR
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;
    virtual FString GetDescription() const override;

    virtual int32 Compile(FMaterialCompiler* C, int32 OutputIndex) override;
#endif

private:
    static constexpr TCHAR UVName[] = TEXT("UV");
    static constexpr TCHAR PositionName[] = TEXT("Position");
    static constexpr TCHAR SizeName[] = TEXT("Size");
    static constexpr TCHAR TilingName[] = TEXT("Tiling");
    static constexpr TCHAR SoftnessName[] = TEXT("Softness");
    static constexpr TCHAR NoSoftnessName[] = TEXT("NoSoftness");
};
