// Copyright Anton Piruev. All Rights Reserved. You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELBCharCameraMode : uint8
{
    FreeCam UMETA(DisplayName = "FreeCam"),
    Strafe UMETA(DisplayName = "Strafe"),
    Aim UMETA(DisplayName = "Aim"),
    TwinStick UMETA(DisplayName = "TwinStick")
};

UENUM(BlueprintType)
enum class ELBCharCameraStyle : uint8
{
    Close UMETA(DisplayName = "Close"),
    Medium UMETA(DisplayName = "Medium"),
    Far UMETA(DisplayName = "Far"),
    CenteredFar UMETA(DisplayName = "CenteredFar")
};
