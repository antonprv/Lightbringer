// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "View/Pawns/CharacterBase.h"

#include "Interfaces/ShadowCaster.h"
#include "Interfaces/PlayerControllable.h"

// Motion matching interfaces
#include "Interfaces/AnimationPropSender.h"
#include "Interfaces/CameraPropSender.h"
#include "Interfaces/TraversalPropSender.h"

#include "LBPlayerCharacter.generated.h"

class AActor;
class UCharacterMoverComponent;
class USkeletalMeshComponentBudgeted;
class UCapsuleComponent;
class UGameplayCameraComponent;
class UMotionWarpingComponent;
class UNavMoverComponent;

class ULBCharacterMovementComponent;
class UComponentsDelegateMediator;

class ALBWeaponBase;

class UHealthComponent;
class UWeaponComponent;
class UFakeShadowComponent;

class ULBPlayerAnimationComponent;
class UAnimUpdateRateOptimizationComponent;

class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;

UCLASS()
class LIGHTBRINGER_API ALBPlayerCharacter : public ACharacterBase,
                                            public IPlayerControllable,
                                            public IShadowCaster,
                                            public IAnimationPropSender,
                                            public ICameraPropSender,
                                            public ITraversalPropSender
{
    GENERATED_BODY()

public:
    // ======================================================
    // Unreal Components
    // ======================================================

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Animation")
    UMotionWarpingComponent* MotionWarping{nullptr};

    // ======================================================
    // Lightbringer Components
    // ======================================================

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | Gameplay | Health")
    UHealthComponent* HealthComponent{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | Gameplay | Health")
    UTextRenderComponent* TextRenderComponent{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
        Category = "Components | View | Shadow")
    UFakeShadowComponent* FakeShadowComponent{nullptr};

protected:
    // ======================================================
    // Controller Interfaces
    // ======================================================
    virtual void MoveCustom_Implementation(const FVector2D Value) override;
    virtual void PickUp_Implementation() override;

    // ======================================================
    // Motion Matching Interfaces
    // ======================================================

    // Setters -----------------
    virtual void SetCharacterInputState_Implementation(
        const FPlayerInputState& PlayerInputState) override;

    // Getters (Out Params)-----
    virtual void GetPropertiesForAnimation_Implementation(
        FLBCharPropertiesForAnimation& OutPropertiesForAnimation) override;
    virtual void GetPropertiesForCamera_Implementation(
        FLBCharPropertiesForCamera& OutPropertiesForCamera) override;
    virtual void GetPropertiesForTraversal_Implementation(
        FLBCharPropertiesForTraversal& OutPropertiesForTraversal) override;

    // ======================================================
    // Fake Shadow Interfaces
    // ======================================================
    virtual void GetShadowCasterMesh_Implementation(
        USkeletalMeshComponent*& OutMesh) override;

public:
    ALBPlayerCharacter(const FObjectInitializer& ObjInit);

    UFUNCTION(BlueprintPure, Category = "Character Movement")
    void GetMovementValues(float& OutForwardInput, float& OutRightInput);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    UComponentsDelegateMediator* ComponentsDelegateMediator{nullptr};

    float ForwardInput{0.f};
    float RightInput{0.f};

    bool bWasFalling{false};
    bool bIsMovementAllowed{false};

    void HandleActorDeath(AActor* DeadActor);
    void DisplayHealth(const float& CurrentHealth);

    UFUNCTION()
    void HandleLanding(const FHitResult& HitResult, const float& LandingSpeed);

    UFUNCTION()
    void HandleDestruction(AActor* DestroyedActor);

    void BindDelegates();
};
