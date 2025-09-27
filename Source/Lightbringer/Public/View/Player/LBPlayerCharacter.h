// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerControllable.h"
#include "LBPlayerCharacter.generated.h"

class ULBCharacterMovementComponent;
class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UTextRenderComponent;
class ALBWeaponBase;
class UAnimMontage;

UCLASS()
class LIGHTBRINGER_API ALBPlayerCharacter : public ACharacter,
                                            public IPlayerControllable
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ALBPlayerCharacter(const FObjectInitializer& ObjInit);

    // Direct getter for custom movement component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    ULBCharacterMovementComponent* MovementHandlerComponent{nullptr};

    // Getters for other components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* CameraComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArmComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* TextRenderComponent{nullptr};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ALBWeaponBase> WeaponClass{nullptr};

    // Socket info getters
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
    FVector GetWeaponLeftHandSocketLocation()
    {
        UpdateLeftHandLocation();
        return WeaponLeftHandSocketLocation;
    };
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
    FRotator GetWeaponLeftHandSocketRotation()
    {
        UpdateLeftHandRotation();
        return WeaponLeftHandSocketRotation;
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* DeathMontage{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintCameraFOV{100.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintCameraInterpolationSpeed{5.f};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
    virtual void Jump() override;

public:
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

    float DefaultCameraFOV;

    void OnDeath();
    void OnHealthChanged(float CurrentHealth);

    void InterpolateCamera(const float& DeltaSeconds);
    void DisplayText(const float& CurrentHealth);

    UFUNCTION()
    void OnGroundLanding(const FHitResult& Hit);

    UFUNCTION()
    void HandleDestruction(AActor* DestroyedActor);

    UPROPERTY()
    ALBWeaponBase* WeaponMesh{nullptr};
    FVector WeaponLeftHandSocketLocation{FVector::ZeroVector};
    FRotator WeaponLeftHandSocketRotation{FRotator::ZeroRotator};

    void SpawnWeapon();
    void UpdateLeftHandLocation();
    void UpdateLeftHandRotation();
};
