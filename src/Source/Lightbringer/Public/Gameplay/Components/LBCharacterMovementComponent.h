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
    float SprintingSpeed{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float WalkingSpeed{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float SlidingSpeed{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float SlideJumpZVelocity{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float WalkToSprintSmoothing{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float DirectionUpdateSmoothing{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params",
        meta = (Tooltip = "How much we scale player input to banking"))
    float BankingMultiplier{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float BankingUpdateSmoothing{0.f};

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
    bool IsJumping();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsSliding();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsWalkingCustom();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMoving();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMovingForward();

    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMovingRight();

    UFUNCTION(BlueprintCallable, Category = "Movement Rules")
    void SetCanEverJump(bool Value);
    UFUNCTION(BlueprintCallable, Category = "Movement Rules")
    void SetCanEverCrouch(bool Value);
    UFUNCTION(BlueprintCallable, Category = "Movement Rules")
    void SetCanEverSlide(bool Value);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Jump Rules")
    float JumpDelay{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Jump Rules")
    float SlideDelay{0.f};

    UFUNCTION(BlueprintPure, Category = "Ground Movement Speed")
    float GetDefaultWalkSpeed();

    UFUNCTION(BlueprintPure, Category = "Ground Movement Speed")
    float GetBanking();

    // =======================================
    // Movement Handlers
    // =======================================
    void SetForwardInput(const float Value);
    void SetRightInput(const float Value);
    void SetLookUpInput(const float Value);
    void SetTurnAroundInput(const float Value);

    void Sprint(const bool bWantsToSprint);
    void Walk(const bool bWantsToWalk);
    void SlideOrCrouch(const bool bWantsToCrouch);

    void PerformJump();

    // =======================================
    // Condition state checks
    // =======================================
    bool IsSprintForbidden();
    bool IsSlideForbidden();

private:
    bool bIsJumpAllowed{false};
    bool bIsSlideAllowed{false};
    bool bCanSlideJump{false};

    bool bCanEverSlide{false};

    bool bIsMovingForward{false};
    bool bIsMovingBack{false};
    bool bIsNoForwardInput{false};

    bool bIsMovingSideways{false};
    bool bIsMovingRight{false};
    bool bIsMovingLeft{false};

    bool bCanSprint{false};
    bool bCanWalk{false};
    bool bCanSlide{false};

    void SpeedInterpolate();

    float DefaultWalkSpeed{0.f};
    float CurrentMaxWalkSpeed{0.f};

    float CurrentRightValue{0.f};
    float CurrentFowrardValue{0.f};

    float DefaultJumpZVelocity{0.f};

    // Get character lean amount based on input
    float Banking{0.f};
    float NewBanking{0.f};
    void UpdateBanking();

    bool bHasLanded{false};
    
    void SetLandingRules();
    void SetSlidingRules();

    // Jumping Rules
    FTimerHandle JumpHandle;
    void AllowJumping();

    // Sliding Rules
    FTimerHandle SlideHandle;
    void AllowSliding();

    void CheckSprintCondition();
    void CheckSlideCondition();

    void UpdateDesiredRotation();

    UFUNCTION()
    void OnCharacterLanding(const FHitResult& HitResult);
};
