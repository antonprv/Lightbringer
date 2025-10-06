// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestShaders/AnimatedTransitionMask.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#include "ShaderCodeUtils.h"
#endif

UAnimatedTransitionMask::UAnimatedTransitionMask()
{
    MenuCategories.Add(FText::FromString(TEXT("Masks")));

#if WITH_EDITOR
    Desc =
        "Smoothly moves a black-and-white mask from left to right with no gradient.";
#endif
}

#if WITH_EDITOR
void UAnimatedTransitionMask::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(TEXT("Animated Transition Mask"));
}

FString UAnimatedTransitionMask::GetDescription() const
{
    return TEXT(
        "Smoothly moves a black-and-white mask from left to right with no gradient.");
}

int32 UAnimatedTransitionMask::Compile(FMaterialCompiler* C, int32 OutputIndex)
{
    if (!UV.Expression)
    {
        return C->Errorf(MissingInputFmt, UVName);
    }
    if (!Time.Expression)
    {
        return C->Errorf(MissingInputFmt, TimeName);
    }
    if (!Steps.Expression)
    {
        return C->Errorf(MissingInputFmt, StepsName);
    }

    const int32 CodeUV = UV.Compile(C);
    const int32 CodeInTime = Time.Compile(C);
    const int32 CodeSteps = Steps.Compile(C);

    const EMaterialValueType UVType = C->GetType(CodeUV);
    const EMaterialValueType InTimeType = C->GetType(CodeInTime);
    const EMaterialValueType StepsType = C->GetType(CodeSteps);

    if (UVType != MCT_Float2)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, UVName,
            FShaderCodeUtils::CMOTFloat2Name);
    }
    if (InTimeType != MCT_Float)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, TimeName,
            FShaderCodeUtils::ScalarFloatName);
    }
    if (StepsType != MCT_Float)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, StepsName,
            FShaderCodeUtils::ScalarFloatName);
    }

    // return (trunc((ceil(uv * smth) / smth) - (sin(t*3))));

    int32 Trunc = C->Truncate(
        C->Sub(C->Div(C->Ceil(C->Mul(CodeUV, CodeSteps)), CodeSteps),
            C->Sine(CodeInTime)));

    return C->ComponentMask(Trunc, true, false, false, false);
}
#endif
