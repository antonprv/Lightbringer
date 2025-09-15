// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FKey KeyToPress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESimpleInputEventType EventType;
};

USTRUCT(BlueprintType)
struct FSimpleInputBindingArray
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSimpleInputBinding> Bindings;
};

USTRUCT(BlueprintType)
struct FSimpleInputBindingAxis
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FKey KeyToPress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESimpleInputAxisType Axis;

    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        meta = (ClampMin = -1.f, ClampMax = 1.f))
    float Scale = 1.f;
};

USTRUCT(BlueprintType)
struct FSimpleInputBindingAxisArray
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSimpleInputBindingAxis> Bindings;
};

UCLASS()
class SIMPLEINPUT_API UInputActionData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TMap<FName, FSimpleInputBindingArray> Bindings;

    UPROPERTY(EditAnywhere)
    TMap<FName, FSimpleInputBindingAxisArray> AxisBindings;

    UFUNCTION(BlueprintCallable,
        meta = (DisplayName = "Get Binding", OverloadName = "Default"))
    bool GetKeyBindings(
        const FName& ActionName, TArray<FSimpleInputBinding>& OutBindings);

    UFUNCTION(BlueprintCallable,
        meta = (DisplayName = "Get Binding", OverloadName = "With Axis"))
    bool GetAxisBinding(const FName& ActionName,
        TArray<FSimpleInputBindingAxis>& OutAxisBindings);
};
