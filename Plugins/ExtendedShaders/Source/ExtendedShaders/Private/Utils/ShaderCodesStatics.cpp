// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Utils/ShaderCodeStatics.h"
#include "Utils/ShaderCodeTypes.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#include "MaterialExpressionIO.h"
#endif

UShaderCodeStatics::UShaderCodeStatics(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    // Empty for now
}

int32 UShaderCodeStatics::GetMissingInputErrorMSG(FMaterialCompiler* C,
    const FString& NodeName, const int32& InputIndex, const FName& InputName)
{
    return C->Errorf(TEXT("Custom material %s missing input %d (%s)"),
        *NodeName, InputIndex, *InputName.ToString());
}

int32 UShaderCodeStatics::CheckError(const EHLSLError& Error,
    FMaterialCompiler* C, const FString& NodeName,
    const FInputErrorData& InputErrorData)
{
    if (Error == EHLSLError::InputMissingError)
    {
        return GetMissingInputErrorMSG(
            C, NodeName, InputErrorData.InputIndex, InputErrorData.InputName);
    }
    else if (Error == EHLSLError::InputCompilationError)
    {
        return GetCompilationErrorMSG(
            C, NodeName, InputErrorData.InputIndex, InputErrorData.InputName);
    }

    return int32();
}

int32 UShaderCodeStatics::GetCompilationErrorMSG(FMaterialCompiler* C,
    const FString& NodeName, const int32& InputIndex, const FName& InputName)
{
    return C->Errorf(
        TEXT("Custom material %s failed to compile input %d (%s)"), *NodeName,
        InputIndex, *InputName.ToString());
}
