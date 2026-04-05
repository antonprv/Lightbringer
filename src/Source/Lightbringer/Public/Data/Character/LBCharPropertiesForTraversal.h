// Copyright Anton Piruev. All Rights Reserved. You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

#include "Data/Character/LBCharMovementTypes.h"

#include "LBCharPropertiesForTraversal.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UMotionWarpingComponent;

USTRUCT(BlueprintType)
struct FLBCharPropertiesForTraversal
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UCapsuleComponent* Capsule{nullptr};

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    USkeletalMeshComponent* Mesh{nullptr};

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UMotionWarpingComponent* MotionWarping{nullptr};

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharMovementMode MovementMode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharGait Gait;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float Speed;
};