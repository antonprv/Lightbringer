// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR
#include "Materials/MaterialExpressionTextureObjectParameter.h"
#include "Materials/MaterialExpressionFunctionInput.h"
#endif

#include "ShaderCodeTypes.generated.h"

UENUM()
enum class EHLSLError : uint8
{
    NoHLSLCodeError,
    FailedToLoadFileError,
    InputMissingError,
    InputCompilationError,
    Default
};

// Helper struct for better error messaging
USTRUCT()
struct FInputErrorData
{
    GENERATED_USTRUCT_BODY()

    int32 InputIndex;
    FName InputName;
};

USTRUCT()
struct FShaderCodeError
{
    GENERATED_USTRUCT_BODY()

    EHLSLError Error;
    
    FInputErrorData InputErrorData;

    FString HLSLFilePath;
};