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
    ULBCharacterMovementComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float SprintSpeed{1000.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float MovementSmoothingSpeed{2.5f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float SprintSmoothingSpeed{2.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float RotationSpeed{540.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float RunTransitionDelay{0.4f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Ground Movement Params")
    float JumpAirControl{0.2f};

    // Getter for animation blueprint
    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsSprinting();

    // Inline getters
    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMoving() { return bIsMoving; };
    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMovingSideways() { return bIsMovingSideways; };
    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMovingForward() { return bIsMovingForward; };
    UFUNCTION(BlueprintPure, Category = "Ground Movement States")
    bool IsMovingBack() { return bIsMovingBack; };

    // Public bools
    bool bIsMovingRight{false};

    UFUNCTION(BlueprintPure, Category = "Ground Movement Triggers")
    bool IsSprintForbidden();

    UFUNCTION(BlueprintCallable, Category = "Jump Rules")
    void SetIsJumpAllowed(bool Value);
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Jump Rules")
    float JumpDelay{0.2f};

    // Movement Handlers
    void SetForwardInput(const float& Value);
    void SetRightInput(const float& Value);
    void SetLookUpInput(const float& Value);
    void SetTurnAroundInput(const float& Value);
    void SetStartSprinting();
    void SetStopSprinting();
    void PerformJump();

    void SetLandingRules();

private:
    bool bIsJumpAllowed{false};
    bool bWantsToSprint{false};
    bool bIsMovingForward{false};
    bool bIsMovingBack{false};
    bool bIsMovingSideways{false};
    bool bIsMovingLeft{false};
    bool bIsMoving{false};

    float DefaultWalkSpeed{0.f};
    float CurrentMaxWalkSpeed{0.f};

    float CurrentRightValue{0.f};
    float CurrentFowrardValue{0.f};

    void SprintInterp(float DeltaTime);

    // Jumping Rules
    FTimerHandle JumpHandle;
    void AllowJumping();
};
