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
    return C->Errorf(TEXT("Node %s missing input %d (%s)"),
        *NodeName, InputIndex, *InputName.ToString());
}

int32 UShaderCodeStatics::GetNoHLSLCodeErrorMSG(FMaterialCompiler* C)
{
    return C->Errorf(TEXT("No HLSL code specified"));
    ;
}

int32 UShaderCodeStatics::GetFailedToLoadFileError(
    FMaterialCompiler* C, const FString& HLSLFilePath)
{
    return C->Errorf(TEXT("Failed to load HLSL file: %s"), *HLSLFilePath);
}

int32 UShaderCodeStatics::GetCompilationErrorMSG(FMaterialCompiler* C,
    const FString& NodeName, const int32& InputIndex, const FName& InputName)
{
    return C->Errorf(
        TEXT("Custom material %s failed to compile input %d (%s)"), *NodeName,
        InputIndex, *InputName.ToString());
}

int32 UShaderCodeStatics::CheckError(FMaterialCompiler* C,
    const FString& NodeName, const FShaderCodeError& ShaderCodeError)
{
    switch (ShaderCodeError.Error)
    {
        case EHLSLError::InputMissingError:
            return GetMissingInputErrorMSG(C, NodeName,
                ShaderCodeError.InputErrorData.InputIndex,
                ShaderCodeError.InputErrorData.InputName);
            break;
        case EHLSLError::InputCompilationError:
            return GetCompilationErrorMSG(C, NodeName,
                ShaderCodeError.InputErrorData.InputIndex,
                ShaderCodeError.InputErrorData.InputName);
            break;
        case EHLSLError::NoHLSLCodeError:
            return GetNoHLSLCodeErrorMSG(C);
            break;
        case EHLSLError::FailedToLoadFileError:
            return GetFailedToLoadFileError(C, ShaderCodeError.HLSLFilePath);
            break;
        default:
            break;
    }
    return int32();
}