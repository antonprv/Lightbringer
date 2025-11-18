// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Utils/CustomHLSLExpression.h"

#if WITH_EDITOR
#include "MaterialCompiler.h"
#include "MaterialExpressionIO.h"

#include "Misc/FileHelper.h"
#include "Interfaces/IPluginManager.h"
#include "UObject/UnrealType.h"

#include "Utils/ShaderCodeUtils.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogUCustomHLSLExpression, Log, Log)

UCustomHLSLExpression::UCustomHLSLExpression(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = TEXT("CustomHLSL Node");
    FirstOutputName = "return";
}

void UCustomHLSLExpression::SetCategoryAndDescription()
{
    MenuCategories.Add(FText::FromString(FriendlyCategory));

#if WITH_EDITOR
    Desc = FriendlyDescription;
#endif
}

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
        UE_LOG(LogUCustomHLSLExpression, Fatal,
            TEXT("SetManualHLSL received an empty string"))
        return;
    }
    else
    {
        HLSLCode = FString::Printf(TEXT("%s"), *HLSLCodeString);
    }
}

void UCustomHLSLExpression::SetHLSLFilePath(const FString& HLSLFilePathString)
{
    if (HLSLFilePathString.IsEmpty())
    {
        UE_LOG(LogUCustomHLSLExpression, Fatal,
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
    // Create a temporary Custom node
    UMaterialExpressionCustom* TempCustom =
        NewObject<UMaterialExpressionCustom>(this,
            UMaterialExpressionCustom::StaticClass(), NAME_None, RF_Transient);

    FString TempCode;

    if (HLSLFilePath.IsEmpty() && HLSLCode.IsEmpty())
    {
        return C->Errorf(TEXT("No HLSL code specified"));
    }
    else if (HLSLFilePath.IsEmpty() && !HLSLCode.IsEmpty())
    {
        TempCode = HLSLCode;
    }
    else
    {
        if (!FFileHelper::LoadFileToString(TempCode, *HLSLFilePath))
            return C->Errorf(
                TEXT("Failed to load HLSL file: %s"), *HLSLFilePath);
    }

    UE_LOG(LogUCustomHLSLExpression, Display, TEXT("Received HLSL code: %s"),
        *TempCode);

    TempCustom->Code = TempCode;
    TempCustom->OutputType = NodeOutputType;  // Adjust as needed
    TempCustom->Description =
        FString::Printf(TEXT("WRAPPED: %s"), *FriendlyName);

    TempCustom->Inputs.Reset();

    TArray<int32> CompiledInputs{};

    int32 InputNumber = 1;

    for (TPair<FName, FExpressionInput*>& Input : NodeInputs)
    {
        // skip over unnamed inputs
        if (Input.Key.IsNone())
        {
            CompiledInputs.Add(INDEX_NONE);
        }
        else
        {
            if (!Input.Value->Expression)
            {
                return C->Errorf(
                    TEXT("Custom material %s missing input %d (%s)"),
                    *FriendlyName, InputNumber, *Input.Key.ToString());
            }
            int32 InputCode = Input.Value->Compile(C);

            FCustomInput CustomInput;
            CustomInput.Input = *Input.Value;
            CustomInput.InputName = Input.Key;

            TempCustom->Inputs.Add(CustomInput);

            if (InputCode < 0)
            {
                return InputCode;
            }
            CompiledInputs.Add(InputCode);
        }
        ++InputNumber;
    }

    if (NodeAdditionalOutputs.Num() > 0)
    {
        TempCustom->AdditionalOutputs.Reset();

        for (TPair<FName, TEnumAsByte<ECustomMaterialOutputType>> Output :
            NodeAdditionalOutputs)
        {
            FCustomOutput CustomOutput;
            CustomOutput.OutputType = Output.Value;
            CustomOutput.OutputName = Output.Key;

            TempCustom->AdditionalOutputs.Add(CustomOutput);
        }
    }

    TempCustom->IncludeFilePaths = HLSLIncludes;

    return C->CustomExpression(TempCustom, OutputIndex, CompiledInputs);
}
#endif
