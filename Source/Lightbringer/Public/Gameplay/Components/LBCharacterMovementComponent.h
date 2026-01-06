// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LBCharacterMovementComponent.generated.h"

class ACharacter;
class UAnimMontage;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIGHTBRINGER_API ULBCharacterMovementComponent
    : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    ULBCharacterMovementComponent(const FObjectInitializer& ObjInit);

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:
    // =======================================
    // Movement parameters
    // =======================================
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float SprintSpeed{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float WalkingSpeed{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float MovementSmoothingSpeed{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float RotationSpeed{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float RunTransitionDelay{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float JumpAirControl{0.f};

    // =======================================
    // Getters for animation blueprint
    // =======================================
    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsSprinting();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsWalkingCustom();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMoving();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMovingRight();

    UFUNCTION(BlueprintPure, Category = "Ground Movement Triggers")
    bool IsSprintForbidden();

    UFUNCTION(BlueprintCallable, Category = "Jump Rules")
    void SetIsJumpAllowed(bool Value);
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Jump Rules")
    float JumpDelay{0.2f};

    UFUNCTION(BlueprintPure, Category = "Ground Movement Speed")
    float GetDefaultWalkSpeed();

    // =======================================
    // Movement Handlers
    // =======================================
    void SetForwardInput(const float Value);
    void SetRightInput(const float Value);
    void SetLookUpInput(const float Value);
    void SetTurnAroundInput(const float Value);

    void Sprint(const bool bWantsToSprint);
    void Walk(const bool bWantsToWalk);
    void SpeedInterpolate();

    void PerformJump();

    void SetLandingRules();

private:
    bool bIsJumpAllowed{false};

    bool bIsMovingForward{false};
    bool bIsMovingBack{false};

    bool bIsMovingSideways{false};
    bool bIsMovingRight{false};
    bool bIsMovingLeft{false};

    bool bCanSprint{false};
    bool bCanWalk{false};

    float DefaultWalkSpeed{0.f};
    float CurrentMaxWalkSpeed{0.f};

    float CurrentRightValue{0.f};
    float CurrentFowrardValue{0.f};

    // Jumping Rules
    FTimerHandle JumpHandle;
    void AllowJumping();

    void UpdateDesiredRotation();

    UFUNCTION()
    void OnCharacterLanding(const FHitResult& HitResult);
};
