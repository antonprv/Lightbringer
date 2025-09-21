// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerControllable.h"
#include "LBPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UTextRenderComponent;
class UAnimMontage;

UCLASS()
class LIGHTBRINGER_API ALBPlayerCharacter : public ACharacter,
                                            public IPlayerControllable
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ALBPlayerCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* CameraComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArmComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* TextRenderComponent{nullptr};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* DeathMontage{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintCameraFOV{100.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintCameraInterpolation{0.1f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed{1000.f};

    UFUNCTION(BlueprintPure, Category = "Movement")
    bool IsSprinting();
    UFUNCTION(BlueprintPure, Category = "Movement")
    bool WantsToSprint() { return bWantsToSprint; };

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

    virtual void Jump() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;  // Tick disabled for now

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    virtual void MoveForwardCustom_Implementation(const float& Value) override;
    virtual void MoveRightCustom_Implementation(const float& Value) override;
    virtual void LookUpCustom_Implementation(const float& Value) override;
    virtual void TurnAroundCustom_Implementation(const float& Value) override;
    virtual void JumpCustom_Implementation() override;
    virtual void StartSprinting_Implementation() override;
    virtual void StopSprinting_Implementation() override;

private:
    float CurrentCameraFOV{0.f};

    bool bIsDying{false};
    bool bWantsToSprint{false};
    bool bIsMovingForward{false};

    float DefaultWalkSpeed;
    float DefaultCameraFOV;

    void OnDeath();
    void OnHealthChanged(float CurrentHealth);

    void InterpolateCamera(const float& DeltaTime);
    void DisplayText(const float& CurrentHealth);

    UFUNCTION()
    void OnGroundLanding(const FHitResult& Hit);
};
