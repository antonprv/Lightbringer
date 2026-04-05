// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "CharacterBase.generated.h"

class AActor;
class UCharacterMoverComponent;
class UCommonLegacyMovementSettings;
class USkeletalMeshComponentBudgeted;
class UCapsuleComponent;
class UGameplayCameraComponent;

class ULBPlayerAnimationComponent;
class UAnimUpdateRateOptimizationComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLandingSignature,
    const FHitResult&, HitResult, const float&, JumpVelocity);

UCLASS()
class LIGHTBRINGER_API ACharacterBase : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ACharacterBase(const FObjectInitializer& ObjInit);

    // ======================================================
    // Unreal Components
    // ======================================================
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
        Category = "Components | View | Collision")
    UCapsuleComponent* Capsule{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
        Category = "Components | View | Camera")
    UGameplayCameraComponent* GameplayCamera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
        Category = "Components | View | Mesh")
    USkeletalMeshComponentBudgeted* Mesh{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | Gameplay | Movement")
    UCharacterMoverComponent* CharacterMover{nullptr};

    // ======================================================
    // Lightbringer Components
    // ======================================================
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Animation")
    UAnimUpdateRateOptimizationComponent* AnimUpdateRateComponent{nullptr};

    UFUNCTION(BlueprintCallable)
    bool IsControlledByPlayer();

    UPROPERTY(BlueprintAssignable, Category = "Movement")
    FOnLandingSignature OnLanding;

    // Names for overriding
    static FName CharacterMeshName;
    static FName MoverComponentName;
    static FName AnimUpdateRateComponentName;

protected:
    // Called when the game starts or when spawned
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY()
    UCommonLegacyMovementSettings* LegacyMovementSettings;

public:
    virtual USkeletalMeshComponentBudgeted* GetMesh() const;
    virtual UCharacterMoverComponent* GetCharacterMovement() const;

private:
    float JumpVelocity;
    bool bWasFalling{false};
    FHitResult GroundHit;

    void ResolveGroundHit();
};
