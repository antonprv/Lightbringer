// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerControllable.h"
#include "LBPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SpwintCameraFOV{100.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed{1000.f};

    UFUNCTION(BlueprintPure, Category = "Movement")
    bool GetIsSprinting() { return bIsSprinting; };

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

    virtual void MoveForward_Implementation(float& Value) override;
    virtual void MoveRight_Implementation(float& Value) override;
    virtual void LookUp_Implementation(float& Value) override;
    virtual void TurnAround_Implementation(float& Value) override;
    virtual void JumpUp_Implementation() override;
    virtual void StartSprinting_Implementation() override;
    virtual void StopSprinting_Implementation() override;

private:
    bool bIsSprinting{false};

    float DefaultWalkSpeed;
    float DefaultCameraFOV;
};
