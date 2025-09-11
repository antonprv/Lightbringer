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

USTRUCT(BlueprintType)
struct FSimpleInputBinding
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FKey KeyToPress;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    ESimpleInputEventType EventType;
};

UCLASS(abstract, Blueprintable)
class SIMPLEINPUT_API UInputActionData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TMap<FName, FSimpleInputBinding> Bindings;

    UFUNCTION(BlueprintCallable)
    bool GetBinding(const FName& ActionName, FSimpleInputBinding& OutBinding);
};
