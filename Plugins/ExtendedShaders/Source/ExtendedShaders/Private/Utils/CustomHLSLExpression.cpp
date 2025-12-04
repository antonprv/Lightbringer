// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Utils/CustomHLSLExpression.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#include "MaterialExpressionIO.h"

#include "Misc/FileHelper.h"
#include "Interfaces/IPluginManager.h"
#include "UObject/UnrealType.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogUCustomHLSLExpression, Log, Log)

UCustomHLSLExpression::UCustomHLSLExpression(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = TEXT("CustomHLSL Node");
    FirstOutputName = "return";
}

// Node interface
void UCustomHLSLExpression::AddNodeInput(
    const FName& InputName, FExpressionInput& ExpressionInput)
{
    NodeInputs.Add(InputName, &ExpressionInput);
}

void UCustomHLSLExpression::AddNodeOutput(const FName& OutputName,
    const TEnumAsByte<ECustomMaterialOutputType>& OutputType)
{
    NodeAdditionalOutputs.Add(OutputName, OutputType);
}

void UCustomHLSLExpression::AddHLSLIncludePath(const FString& IncludePath) 
{
    HLSLIncludes.Add(IncludePath);
}

void UCustomHLSLExpression::SetCategoryAndDescription()
{
    MenuCategories.Add(FText::FromString(FriendlyCategory));

#if WITH_EDITOR
    Desc = FriendlyDescription;
#endif
}

/**
 * Applies set name to the first node output and adds additional outputs.
 */
void UCustomHLSLExpression::UpdateNodeOutputs()
{
    if (NodeAdditionalOutputs.Num() == 0) return;

    bShowOutputNameOnPin = true;

    SetFirstOuputName(FirstOutputName);

    for (TPair<FName, TEnumAsByte<ECustomMaterialOutputType>> Output :
        NodeAdditionalOutputs)
    {
        Outputs.Add(FExpressionOutput(Output.Key));
    }
}

void UCustomHLSLExpression::SetFirstOuputName(FName OutputName)
{
    if (OutputName.IsNone()) return;

    bShowOutputNameOnPin = true;
    Outputs[0].OutputName = OutputName;
}

void UCustomHLSLExpression::SetManualHLSL(const FString& HLSLCodeString)
{
    if (HLSLCodeString.IsEmpty())
    {
        UE_LOG(LogUCustomHLSLExpression, Error,
            TEXT("SetManualHLSL received an empty string"))
        return;
    }
    else
    {
        HLSLCode = FString::Printf(TEXT("%s"), *HLSLCodeString);
    }
}

void UCustomHLSLExpression::SetNodeOutputType(
    TEnumAsByte<ECustomMaterialOutputType> Type)
{
    NodeOutputType = Type;
}

void UCustomHLSLExpression::SetHLSLFilePath(const FString& HLSLFilePathString)
{
    if (HLSLFilePathString.IsEmpty())
    {
        UE_LOG(LogUCustomHLSLExpression, Error,
            TEXT("SetHLSLFilePath received an empty string"))
        return;
    }
    else
    {
        FString PluginDir = IPluginManager::Get()
                                .FindPlugin(TEXT("ExtendedShaders"))
                                ->GetBaseDir();
        HLSLFilePath = FPaths::Combine(
            PluginDir, FString::Printf(TEXT("%s"), *HLSLFilePathString));
    }
}

#if WITH_EDITOR

void UCustomHLSLExpression::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(FriendlyName);
}

FString UCustomHLSLExpression::GetDescription() const
{
    return FriendlyDescription;
}

int32 UCustomHLSLExpression::Compile(FMaterialCompiler* C, int32 OutputIndex)
{
    FString TempCode;

    ErrorData.Error = LoadHLSLCode(TempCode);
    ErrorData.HLSLFilePath = HLSLFilePath;
    if (ErrorData.Error != EHLSLError::Default)
    {
        return UShaderCodeStatics::CheckError(C, FriendlyName, ErrorData);
    }

    UMaterialExpressionCustom* TempCustom = CreateTempCustomNode(TempCode);
    SetupAdditionalOutputs(TempCustom);
    TArray<int32> CompiledInputs;
    ErrorData.Error =
        CompileInputs(C, TempCustom, CompiledInputs, ErrorData.InputErrorData);
    if (ErrorData.Error != EHLSLError::Default)
    {
        return UShaderCodeStatics::CheckError(C, FriendlyName, ErrorData);
    }

    return C->CustomExpression(TempCustom, OutputIndex, CompiledInputs);
}

// Load code and react to possible errors
EHLSLError UCustomHLSLExpression::LoadHLSLCode(FString& OutTempCode)
{
    if (HLSLFilePath.IsEmpty() && HLSLCode.IsEmpty())
    {
        return EHLSLError::NoHLSLCodeError;
    }
    else if (HLSLFilePath.IsEmpty() && !HLSLCode.IsEmpty())
    {
        OutTempCode = HLSLCode;
    }
    else
    {
        if (!FFileHelper::LoadFileToString(OutTempCode, *HLSLFilePath))
        {
            return EHLSLError::FailedToLoadFileError;
        }
    }

    UE_LOG(LogUCustomHLSLExpression, Display, TEXT("Received HLSL code: %s"),
        *OutTempCode);

    return EHLSLError::Default;
}

// Create and fully setup UMaterialExpressionCustom node
UMaterialExpressionCustom* UCustomHLSLExpression::CreateTempCustomNode(
    const FString& Code)
{
    UMaterialExpressionCustom* TempCustom =
        NewObject<UMaterialExpressionCustom>(this,
            UMaterialExpressionCustom::StaticClass(), NAME_None, RF_Transient);

    TempCustom->Code = Code;
    TempCustom->OutputType = NodeOutputType;
    TempCustom->Description =
        FString::Printf(TEXT("WRAPPED: %s"), *FriendlyName);
    TempCustom->Inputs.Reset();
    TempCustom->AdditionalOutputs.Reset();

    TempCustom->IncludeFilePaths = HLSLIncludes;

    return TempCustom;
}

// Prepare Inputs and add to the temporary custom node
// if something goes wrog return error and an input name
EHLSLError UCustomHLSLExpression::CompileInputs(FMaterialCompiler* C,
    UMaterialExpressionCustom* TempCustom, TArray<int32>& OutCompiledInputs,
    FInputErrorData& OutInputErrorData)
{
    if (NodeInputs.Num() == 0)
    {
        return EHLSLError::Default;
    }

    // Count inputs for more detailed error message
    OutInputErrorData.InputIndex = 1;

    for (TPair<FName, FExpressionInput*>& Input : NodeInputs)
    {
        if (Input.Key.IsNone())
        {
            OutCompiledInputs.Add(INDEX_NONE);
            continue;
        }

        if (!Input.Value->Expression)
        {
            OutInputErrorData.InputName = Input.Key;
            return EHLSLError::InputMissingError;
        }

        int32 InputCode = Input.Value->Compile(C);
        if (InputCode < 0)
        {
            OutCompiledInputs = {InputCode};
            return EHLSLError::InputCompilationError;
        }

        FCustomInput CustomInput;
        CustomInput.InputName = Input.Key;
        CustomInput.Input = *Input.Value;

        TempCustom->Inputs.Add(CustomInput);
        OutCompiledInputs.Add(InputCode);
        ++OutInputErrorData.InputIndex;
    }

    return EHLSLError::Default;
}

// Prepare Additional Outputs of the temporary custom node
void UCustomHLSLExpression::SetupAdditionalOutputs(
    UMaterialExpressionCustom* TempCustom)
{
    if (NodeAdditionalOutputs.Num() == 0) return;

    TempCustom->AdditionalOutputs.Reset();
    for (TPair<FName, TEnumAsByte<ECustomMaterialOutputType>> Output :
        NodeAdditionalOutputs)
    {
        FCustomOutput CustomOutput;
        CustomOutput.OutputType = Output.Value;
        CustomOutput.OutputName = Output.Key;
        TempCustom->AdditionalOutputs.Add(CustomOutput);
    }

    TempCustom->AdditionalOutputs;
}
#endif