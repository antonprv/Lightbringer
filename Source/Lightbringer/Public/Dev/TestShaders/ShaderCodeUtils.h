// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class FShaderCodeUtils
{
public:
    FShaderCodeUtils();
    ~FShaderCodeUtils();

public:
    // Expects 1 parameter - input name
    static constexpr TCHAR MissingInputFmt[] = TEXT("Missing input '%s'");

    // Expects 2 parameters - input name and type name
    static constexpr TCHAR WrongTypeFmt[] = TEXT("Input '%s' must be a '%s'");

    // HLSL float2 type name
    static constexpr TCHAR CMOTFloat2Name[] = TEXT("float2");

    // HLSL float1 type name
    static constexpr TCHAR CMOTFloat1Name[] = TEXT("float1");

    // HLSL float type name
    static constexpr TCHAR ScalarFloatName[] = TEXT("float");
};
