// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LBCharacterMovementComponent.generated.h"

class ACharacter;

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

    // Numeric movement values
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed{1000.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float MovementSmoothingSpeed{2.5f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintSmoothingSpeed{2.f};

    // Getters for animation blueprint
    UFUNCTION(BlueprintPure, Category = "Movement")
    bool IsSprintForbidden();
    UFUNCTION(BlueprintPure, Category = "Movement")
    bool IsSprinting();

    // Inline getters
    UFUNCTION(BlueprintPure, Category = "Movement")
    bool IsMoving() { return bIsMoving; };
    UFUNCTION(BlueprintPure, Category = "Movement")
    bool IsMovingSideways() { return bIsMovingSideways; };

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetIsJumpAllowed(bool Value);

    // Movement Handlers
    void SetForwardInput(const float& Value);
    void SetRightInput(const float& Value);
    void SetLookUpInput(const float& Value);
    void SetTurnAroundInput(const float& Value);
    void SetStartSprinting();
    void SetStopSprinting();
    void PerformJump();

private:
    bool bIsJumpAllowed{false};
    bool bWantsToSprint{false};
    bool bIsMovingForward{false};
    bool bIsMovingBack{false};
    bool bIsMovingSideways{false};
    bool bIsMoving{false};

    float DefaultWalkSpeed{0.f};
    float CurrentMaxWalkSpeed{0.f};

    float CurrentRightValue{0.f};
    float CurrentFowrardValue{0.f};

    void SprintInterp(float DeltaTime);
    void SetRotationRules();
};
