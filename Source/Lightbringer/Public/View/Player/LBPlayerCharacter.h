// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerControllable.h"
#include "LBPlayerCharacter.generated.h"

class AActor;

class ULBCharacterMovementComponent;
class UComponentsDelegateMediator;

class ALBWeaponBase;

class UHealthComponent;
class UWeaponComponent;
class UAnimationComponent;

class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;
class UDecalComponent;

UCLASS()
class LIGHTBRINGER_API ALBPlayerCharacter : public ACharacter,
                                            public IPlayerControllable
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ALBPlayerCharacter(const FObjectInitializer& ObjInit);

    // Direct getter for custom movement component
    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, Category = "Components | Other")
    ULBCharacterMovementComponent* MovementHandlerComponent{nullptr};
    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, Category = "Components | Other")
    UWeaponComponent* WeaponComponent{nullptr};
    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, Category = "Components | Other")
    UAnimationComponent* AnimationComponent{nullptr};

    // Getters for other components
    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, Category = "Components | Camera")
    UCameraComponent* CameraComponent{nullptr};
    UPROPERTY(
        VisibleAnywhere, BlueprintReadOnly, Category = "Components | Camera")
    USpringArmComponent* SpringArmComponent{nullptr};

    UPROPERTY(
        VisibleAnywhere, BlueprintReadWrite, Category = "Components | Health")
    UHealthComponent* HealthComponent{nullptr};
    UPROPERTY(
        VisibleAnywhere, BlueprintReadWrite, Category = "Components | Health")
    UTextRenderComponent* TextRenderComponent{nullptr};

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
        Category = "Components | Decal Shadow")
    UDecalComponent* DecalShadow{nullptr};
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Components | Decal Shadow")
    bool bIsDecalShadowDebugEnabled{false};
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
        Category = "Components | Decal Shadow", meta = (ClampMin = "0"))
    float DecalTraceDistance{1000.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintCameraFOV{100.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintCameraInterpolationSpeed{5.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float SprintRightCameraInterpolationSpeed{0.8f};

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
    UPROPERTY()
    UComponentsDelegateMediator* ComponentsDelegateMediator{nullptr};

    float CurrentCameraFOV{0.f};
    float DefaultCameraFOV{0.f};

    float CurrentSocketRightOffset{0.f};
    float DefaultSocketRightOffset{0.f};

    float DefaultSprintRightCameraInterpolationSpeed{0.f};

    void HandleActorDeath(AActor* DeadActor);
    void OnHealthChanged(float CurrentHealth);

    void InterpolateSprintCamera(const float& DeltaSeconds);
    void InterpolateSprintRightCamera(const float& DeltaSeconds);
    void DisplayText(const float& CurrentHealth);

    UFUNCTION()
    void OnGroundLanding(const FHitResult& Hit);

    UFUNCTION()
    void HandleDestruction(AActor* DestroyedActor);

    bool bHasDecalHit{false};
    FHitResult DecalHitResult;
    FVector DecalStartHit{FVector::ZeroVector};
    FVector DecalEndHit{FVector::ZeroVector};
    void UpdateDecalTransform();
};
