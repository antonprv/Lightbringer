// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "ShaderCodeTypes.h"
#include "ShaderCodeStatics.generated.h"
/**
 *
 */

class FMaterialCompiler;

UCLASS()
class EXTENDEDSHADERS_API UShaderCodeStatics : public UObject
{
    GENERATED_BODY()

public:
    UShaderCodeStatics(const FObjectInitializer& ObjInit);

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

    static int32 CheckError(const EHLSLError& Error, FMaterialCompiler* C,
        const FString& NodeName, const FInputErrorData& InputErrorData);

    static int32 GetCompilationErrorMSG(FMaterialCompiler* C,
        const FString& NodeName, const int32& InputIndex,
        const FName& InputName);
    static int32 GetMissingInputErrorMSG(FMaterialCompiler* C,
        const FString& NodeName, const int32& InputIndex,
        const FName& InputName);
};
