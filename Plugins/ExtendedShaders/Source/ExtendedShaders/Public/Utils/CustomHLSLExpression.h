// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR
#include "Materials/MaterialExpressionCustom.h"
#include "Utils/ShaderCodeStatics.h"
#else
enum ECustomMaterialOutputType : int;
#endif

#include "CustomHLSLExpression.generated.h"

/**
 * Abstract HLSL wrapper class, create a child of it if you want to add custom
 * HLSL files to the game.
 */

class FMaterialCompiler;
struct FExpressionInput;

UENUM()
enum class ENodeInputType : uint8
{
    TextureObject
};

USTRUCT()
struct FTypedInput
{
    GENERATED_USTRUCT_BODY()

    FExpressionInput* ExpressionInput;
    ENodeInputType Type;

    FTypedInput() = default;

    FTypedInput(FExpressionInput* InExpressionInput, ENodeInputType InType)
        : ExpressionInput(InExpressionInput), Type(InType)
    {
    }
};

UCLASS()
class EXTENDEDSHADERS_API UCustomHLSLExpression : public UMaterialExpression
{
    GENERATED_BODY()

public:
    // This is where all child classes must declare default values and call
    // SetCategoryAndDescription();
    UCustomHLSLExpression(const FObjectInitializer& ObjInit);

    FString FriendlyDescription;
    FString FriendlyName;
    FString FriendlyCategory;

    FName FirstOutputName{""};

    void AddNodeInput(
        const FName& InputName, FExpressionInput& ExpressionInput);

    void AddNodeTypedInput(const FName& InputName,
        FExpressionInput& ExpressionInput, const ENodeInputType& InputType);
    void AddNodeTypedInput(
        const FName& InputName, const FTypedInput& TypedInput);

    void AddNodeOutput(const FName& OutputName,
        const TEnumAsByte<ECustomMaterialOutputType>& OutputType);

    void SetHLSLFilePath(const FString& HLSLFilePathString);
    // You can still write code manually and send it here
    void SetManualHLSL(const FString& HLSLCodeString);

    void SetCategoryAndDescription();
    void UpdateNodeOutputs();
    void SetFirstOuputName(FName OutputName);

protected:
    TEnumAsByte<ECustomMaterialOutputType> NodeOutputType;

    TMap<FName, FExpressionInput*> NodeInputs;

    TMap<FName, FTypedInput> NodeTypedInputs;

    TMap<FName, TEnumAsByte<ECustomMaterialOutputType>> NodeAdditionalOutputs;

    TArray<FString> HLSLIncludes;

#if WITH_EDITOR
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;
    virtual FString GetDescription() const override;

    virtual int32 Compile(FMaterialCompiler* C, int32 OutputIndex) override;
#endif

private:
    FString HLSLCode;
    FString HLSLFilePath;

    EHLSLError LoadHLSLCode(FString& OutTempCode);

    UMaterialExpressionCustom* CreateTempCustomNode(const FString& Code);

    EHLSLError CompileInputs(FMaterialCompiler* C,
        UMaterialExpressionCustom* TempCustom,
        TArray<int32>& OutCompiledInputs, FInputErrorData& OutInputErrorData);

    EHLSLError CompileTypedInputs(FMaterialCompiler* C,
        const int32& OutputIndex, UMaterialExpressionCustom* TempCustom,
        TArray<int32>& OutCompiledInputs, FInputErrorData& OutInputErrorData);

    EHLSLError CompileTextureObject(FMaterialCompiler* C,
        const int32& OutputIndex, UMaterialExpressionCustom* TempCustom,
        TArray<int32>& OutCompiledInputs, FExpressionInput* TextureInput,
        const FName& InputName);

    void SetupAdditionalOutputs(UMaterialExpressionCustom* OutTempCustom);
};
