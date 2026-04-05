// Copyright Anton Piruev. All Rights Reserved. You can use this project
// non-commercially for educational purposes, any commercial use, derivative
// commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TraversalPropSender.generated.h"

struct FLBCharPropertiesForTraversal;

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UTraversalPropSender : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class LIGHTBRINGER_API ITraversalPropSender
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be
    // inherited to implement this interface.
public:
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void GetPropertiesForTraversal(
        FLBCharPropertiesForTraversal& OutPropertiesForTraversal);

    virtual void GetPropertiesForTraversal_Implementation(
        FLBCharPropertiesForTraversal& OutPropertiesForTraversal);
};
