// Copyright Anton Piruev. All Rights Reserved. You can use this project
// non-commercially for educational purposes, any commercial use, derivative
// commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

#include "Data/Character/LBCharCameraTypes.h"
#include "Data/Character/LBCharMovementTypes.h"

#include "LBCharPropertiesForCamera.generated.h"

USTRUCT(BlueprintType)
struct FLBCharPropertiesForCamera
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharCameraStyle CameraStyle;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharCameraMode CameraMode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharGait Gait;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharStance Stance;
};