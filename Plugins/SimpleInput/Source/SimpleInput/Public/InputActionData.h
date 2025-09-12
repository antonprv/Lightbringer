// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputCoreTypes.h"
#include "InputActionData.generated.h"

/**
 * Allows for creation og Input Actions through Unreal Engine's Data Assets
 */

UENUM(BlueprintType)
enum class ESimpleInputEventType : uint8
{
    Pressed,
    Released
};

UENUM(BlueprintType)
enum class ESimpleInputAxisType : uint8
{
    X,
    Y
};

USTRUCT(BlueprintType)
struct FSimpleInputBinding
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FKey KeyToPress;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ESimpleInputEventType EventType;
};

USTRUCT(BlueprintType)
struct FSimpleInputBindingAxis
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FKey KeyToPress;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ESimpleInputAxisType Axis;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Scale = 1.f;
};

UCLASS(abstract, Blueprintable)
class SIMPLEINPUT_API UInputActionData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TMap<FName, FSimpleInputBinding> Bindings;

    UPROPERTY(EditAnywhere)
    TMap<FName, FSimpleInputBindingAxis> AxisBindings;

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Binding", OverloadName = "Default"))
    bool GetBinding(const FName& ActionName, FSimpleInputBinding& OutBinding);
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Binding", OverloadName = "With Axis"))
    bool GetAxisBinding(const FName& ActionName, FSimpleInputBindingAxis& OutAxisBinding);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Binding", OverloadName = "Default"))
    void SetBinding(const FName& ActionName, FKey& KeyToPress);
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Binding", OverloadName = "With Axis"))
    void SetAxisBinding(const FName& ActionName, FKey& KeyToPress);
};
