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

    virtual void Jump() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;  // Tick disabled for now

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    virtual void MoveForward_Implementation(const float& Value) override;
    virtual void MoveRight_Implementation(const float& Value) override;
    virtual void LookUp_Implementation(const float& Value) override;
    virtual void TurnAround_Implementation(const float& Value) override;
    virtual void JumpUp_Implementation() override;
    virtual void StartSprinting_Implementation() override;
    virtual void StopSprinting_Implementation() override;

private:
    float CurrentCameraFOV{0.f};

    bool bWantsToSprint{false};
    bool bIsMovingForward{false};

    float DefaultWalkSpeed;
    float DefaultCameraFOV;

    void InterpolateCamera(const float& DeltaTime);
    void DisplayText();
};
