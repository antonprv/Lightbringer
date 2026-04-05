// Copyright Anton Piruev. All Rights Reserved. You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

#include "Data/Player/PlayerInputState.h"
#include "Data/Character/LBCharMovementTypes.h"

#include "LBCharPropertiesForAnimation.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UMotionWarpingComponent;

USTRUCT(BlueprintType)
struct FLBCharPropertiesForAnimation
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FPlayerInputState InputState;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharMovementMode MovementMode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharStance Stance;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharRotationMode RotationMode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharGait Gait;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELBCharMovementDirection MovementDirection;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FTransform ActorTransform;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector Velocity;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector InputAcceleration;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float CurrentMaxAcceleration;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float CurrentMaxDeceleration;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FRotator OrientationIntent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FRotator AimingRotation;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool JustLanded;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector LandVelocity;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float SteeringTime;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector GroundNormal;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector GroundLocation;
};