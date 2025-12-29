// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Components/SkeletalMeshComponent.h"

#include "ShadowCaster.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UShadowCaster : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FAKESHADOW_API IShadowCaster
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(
        BlueprintCallable, BlueprintNativeEvent, Category = "Process Input")
    void GetShadowCasterMesh(USkeletalMeshComponent*& OutMesh);

	virtual void GetShadowCasterMesh_Implementation(
        USkeletalMeshComponent*& OutMesh) =0;
};
