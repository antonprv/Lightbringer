// Copyright Anton Piruev. All Rights Reserved. You can use this project
// non-commercially for educational purposes, any commercial use, derivative
// commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELBCharGait : uint8
{
    Walk UMETA(DisplayName = "Walk"),
    Run UMETA(DisplayName = "Run"),
    Sprint UMETA(DisplayName = "Sprint")
};

UENUM(BlueprintType)
enum class ELBCharMovementDirection : uint8
{
    F UMETA(DisplayName = "F"),
    B UMETA(DisplayName = "B"),
    LL UMETA(DisplayName = "LL"),
    LR UMETA(DisplayName = "LR"),
    RL UMETA(DisplayName = "RL"),
    RR UMETA(DisplayName = "RR")
};

UENUM(BlueprintType)
enum class ELBCharMovementDirectionBias : uint8
{
    LeftFootForward UMETA(DisplayName = "LeftFootForward"),
    RightFootForward UMETA(DisplayName = "BRightFootForward")
};

UENUM(BlueprintType)
enum class ELBCharMovementMode : uint8
{
    OnGround UMETA(DisplayName = "OnGround"),
    InAir UMETA(DisplayName = "InAir"),
    Sliding UMETA(DisplayName = "Sliding"),
    Traversing UMETA(DisplayName = "Traversing")
};

UENUM(BlueprintType)
enum class ELBharacterMovementState : uint8
{
    Idle UMETA(DisplayName = "Idle"),
    Walking UMETA(DisplayName = "Walking")
};

UENUM(BlueprintType)
enum class ELBCharRotationMode : uint8
{
    OrientToMovement UMETA(DisplayName = "OrientToMovement"),
    Strafe UMETA(DisplayName = "Strafe"),
    Aim UMETA(DisplayName = "Aim")
};

UENUM(BlueprintType)
enum class ELBCharStance : uint8
{
    Stand UMETA(DisplayName = "Stand"),
    Crouch UMETA(DisplayName = "Crouch")
};

UENUM(BlueprintType)
enum class ELBCharTraversalActionType : uint8
{
    None UMETA(DisplayName = "None"),

    Hurdle UMETA(DisplayName = "Hurdle",
        Tooltip =
            "Traverse over a thin object and end on the ground at a similar level (Low fence)"),

    Vault UMETA(DisplayName = "Vault",
        Tooltip =
            "Traverse over a thin object and end in a falling state (Tall fence, or elevated obstacle with no floor on the other side)"),

    Mantle UMETA(DisplayName = "Mantle", 
        Tooltip = "Traverse up and onto an object without passing over it")
};
