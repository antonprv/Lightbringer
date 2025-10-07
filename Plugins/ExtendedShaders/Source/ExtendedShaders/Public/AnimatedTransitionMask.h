// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "AnimatedTransitionMask.generated.h"

/**
 * Smoothly moves black and white mask left to right with no gradient.
 * Simple testing.
 */

class FMaterialCompiler;

UCLASS(
    meta = (DisplayName = "Animated Transition Mask", Category = "Masks",
        Tooltip =
            "Smoothly moves a black - and-white mask from left to right with no gradient."))
class EXTENDEDSHADERS_API UAnimatedTransitionMask : public UMaterialExpression
{
    GENERATED_BODY()

public:
    UAnimatedTransitionMask();

    UPROPERTY()
    FExpressionInput UV;
    UPROPERTY()
    FExpressionInput Time;
    UPROPERTY()
    FExpressionInput Steps;

protected:
#if WITH_EDITOR
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;
    virtual FString GetDescription() const override;

    virtual int32 Compile(FMaterialCompiler* C, int32 OutputIndex) override;
#endif

private:
    static constexpr TCHAR MissingInputFmt[] = TEXT("Missing input '%s'");
    static constexpr TCHAR UVName[] = TEXT("UV");
    static constexpr TCHAR TimeName[] = TEXT("InTime");
    static constexpr TCHAR StepsName[] = TEXT("NumSteps");
};
