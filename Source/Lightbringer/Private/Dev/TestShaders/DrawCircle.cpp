// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "DrawCircle.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#include "ShaderCodeUtils.h"
#endif

UDrawCircle::UDrawCircle()
{
    MenuCategories.Add(FText::FromString(TEXT("Shapes")));

#if WITH_EDITOR
    Desc =
        "Draws a circle, size and position value can be animated externally.";
#endif
}

#if WITH_EDITOR
void UDrawCircle::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(TEXT("Draw Circle"));
}

FString UDrawCircle::GetDescription() const
{
    return TEXT(
        "Draws a circle, size and position value can be animated externally.");
}

int32 UDrawCircle::Compile(FMaterialCompiler* C, int32 OutputIndex)
{
    // check if null
    if (!UV.Expression)
    {
        return C->Errorf(FShaderCodeUtils::MissingInputFmt, UVName);
    }
    if (!Position.Expression)
    {
        return C->Errorf(FShaderCodeUtils::MissingInputFmt, PositionName);
    }
    if (!Size.Expression)
    {
        return C->Errorf(FShaderCodeUtils::MissingInputFmt, SizeName);
    }
    if (!Tiling.Expression)
    {
        return C->Errorf(FShaderCodeUtils::MissingInputFmt, TilingName);
    }
    if (!Softness.Expression)
    {
        return C->Errorf(FShaderCodeUtils::MissingInputFmt, SoftnessName);
    }
    if (!NoSoftness.Expression)
    {
        return C->Errorf(FShaderCodeUtils::MissingInputFmt, NoSoftnessName);
    }

    // get bytecode
    const int32 CodeUV = UV.Compile(C);
    const int32 CodePosition = Position.Compile(C);
    const int32 CodeSize = Size.Compile(C);
    const int32 CodeTiling = Tiling.Compile(C);
    const int32 CodeSoftness = Softness.Compile(C);
    const int32 CodeNoSoftness = NoSoftness.Compile(C);

    // check types
    const EMaterialValueType UVType = C->GetType(CodeUV);
    const EMaterialValueType PositionType = C->GetType(CodePosition);
    const EMaterialValueType NoSoftessType = C->GetType(CodeNoSoftness);

    const EMaterialValueType SizeType = C->GetType(CodeSize);
    const EMaterialValueType TilingType = C->GetType(CodeTiling);
    const EMaterialValueType SoftnessType = C->GetType(CodeSoftness);

    if (UVType != MCT_Float2)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, UVName,
            FShaderCodeUtils::CMOTFloat2Name);
    }
    if (PositionType != MCT_Float2)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, PositionName,
            FShaderCodeUtils::CMOTFloat2Name);
    }
    if (NoSoftessType != MCT_Float)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, NoSoftnessName,
            FShaderCodeUtils::ScalarFloatName);
    }

    if (SizeType != MCT_Float)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, SizeName,
            FShaderCodeUtils::ScalarFloatName);
    }
    if (TilingType != MCT_Float)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, TilingName,
            FShaderCodeUtils::ScalarFloatName);
    }
    if (SoftnessType != MCT_Float)
    {
        return C->Errorf(FShaderCodeUtils::WrongTypeFmt, SoftnessName,
            FShaderCodeUtils::ScalarFloatName);
    }

    // interpret CodeNoSoftness as bool
    const int32 CodeNoSoftnessBool = C->Saturate(CodeNoSoftness);

    // rewrite hlsl
    /*
    float d = length(coord-uv);

    if (!IsSoft)
    {
        return d < size;
    }
    else
    {
        return pow(pow(d, size));
    }
    */

    int32 TiledUV = C->Frac(C->Mul(CodeUV, CodeTiling));
    int32 Length = C->Length(C->Sub(CodePosition, TiledUV));

    // float comparrison can never be presize
    int32 Eps = C->Constant(KINDA_SMALL_NUMBER);

    int32 SharpCircle = C->If(Length, CodeSize,  //
        C->Constant(0.f),                        // d > size
        C->Constant(0.f),                        // d == size
        C->Constant(1.f),                        // d < size
        Eps);

    int32 SmoothCircle = C->Power(Length, CodeSize);

    int32 Condition = C->Lerp(  // if-operator
        SharpCircle,            // true condition
        SmoothCircle,           // false condition
        CodeNoSoftnessBool      // (!IsSoft)
    );

    return Condition;
}

#endif
