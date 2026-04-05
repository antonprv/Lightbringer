// Copyright Anton Piruev. All Rights Reserved. You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputState.generated.h"

USTRUCT(Blueprintable)
struct FPlayerInputState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bWantsToSprint = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bWantsToWalk = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bWantsToStrafe = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bWantsToAim = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool bWantsToCrouch = false;
};