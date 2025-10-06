// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestShaders/AnimatedTransitionMask.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#endif

UAnimatedTransitionMask::UAnimatedTransitionMask()
{
    MenuCategories.Add(FText::FromString(TEXT("Masks")));
}

#if WITH_EDITOR
void UAnimatedTransitionMask::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(TEXT("Animated Transition Mask"));
}

int32 UAnimatedTransitionMask::Compile(FMaterialCompiler* C, int32 OutputIndex)
{
    Super::Compile(C, OutputIndex);

    if (!UV.Expression)
    {
        return C->Errorf(MissingInputFmt, UVName);
    }
    if (!InTime.Expression)
    {
        return C->Errorf(MissingInputFmt, TimeName);
    }
    if (!NumSteps.Expression)
    {
        return C->Errorf(MissingInputFmt, StepsName);
    }

    const int32 CodeUV = UV.Compile(C);
    const int32 CodeInTime = InTime.Compile(C);
    const int32 CodeNumSteps = NumSteps.Compile(C);

    // return (trunc((ceil(uv * smth) / smth) - (sin(t*3))));

    int32 Trunc = C->Truncate(
        C->Sub(C->Div(C->Ceil(C->Mul(CodeUV, CodeNumSteps)), CodeNumSteps),
            C->Sine(CodeInTime)));

    return C->ComponentMask(Trunc, true, false, false, false);
}
#endif
