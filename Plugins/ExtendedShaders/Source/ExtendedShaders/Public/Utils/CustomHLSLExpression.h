// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "CustomHLSLExpression.generated.h"

/**
 * Abstract HLSL wrapper class, create a child of it if you want to add custom
 * HLSL files to the game.
 */

class FMaterialCompiler;
enum ECustomMaterialOutputType;
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

    TEnumAsByte<enum ECustomMaterialOutputType> NodeOutputType;

    TMap<FName, FExpressionInput*> NodeInputs;

    void SetHLSLFilePath(const FString& HLSLFilePathString);

    // You can still write code manually and send it here
    void SetManualHLSL(const FString& HLSLCodeString);

    void SetCategoryAndDescription();

protected:
#if WITH_EDITOR
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;
    virtual FString GetDescription() const override;

    virtual int32 Compile(FMaterialCompiler* C, int32 OutputIndex) override;
#endif

private:
    FString HLSLCode;
    FString HLSLFilePath;
};
