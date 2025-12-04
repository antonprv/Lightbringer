// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR
#include "Materials/MaterialExpressionCustom.h"
#include "Utils/ShaderCodeStatics.h"
#include "Utils/ShaderCodeTypes.h"
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

    void AddNodeOutput(const FName& OutputName,
        const TEnumAsByte<ECustomMaterialOutputType>& OutputType);

    void AddHLSLIncludePath(const FString& IncludePath);

    void SetHLSLFilePath(const FString& HLSLFilePathString);
    // You can still write code manually and send it here
    void SetManualHLSL(const FString& HLSLCodeString);

    void SetNodeOutputType(TEnumAsByte<ECustomMaterialOutputType> Type);

    void SetCategoryAndDescription();
    void UpdateNodeOutputs();
    void SetFirstOuputName(FName OutputName);

protected:
    // TODO: set all of this to private when done refactoring children
    TEnumAsByte<ECustomMaterialOutputType> NodeOutputType;

    TMap<FName, FExpressionInput*> NodeInputs;

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

    
    FShaderCodeError ErrorData;

    EHLSLError LoadHLSLCode(FString& OutTempCode);

    UMaterialExpressionCustom* CreateTempCustomNode(const FString& Code);

    EHLSLError CompileInputs(FMaterialCompiler* C,
        UMaterialExpressionCustom* TempCustom,
        TArray<int32>& OutCompiledInputs, FInputErrorData& OutInputErrorData);

    void SetupAdditionalOutputs(UMaterialExpressionCustom* OutTempCustom);
};
