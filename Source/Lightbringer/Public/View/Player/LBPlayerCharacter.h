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
class UFakeShadowComponent;

class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;

UCLASS()
class LIGHTBRINGER_API ALBPlayerCharacter : public ACharacter,
                                            public IPlayerControllable
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ALBPlayerCharacter(const FObjectInitializer& ObjInit);

    // My custom components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | Gameplay | Other")
    ULBCharacterMovementComponent* MovementHandlerComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | Gameplay | Other")
    UWeaponComponent* WeaponComponent{nullptr};

    // Unreal Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
        Category = "Components | Gameplay | Health")
    UHealthComponent* HealthComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
        Category = "Components | Gameplay | Health")
    UTextRenderComponent* TextRenderComponent{nullptr};

    // My custom components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | View | Animation")
    UAnimationComponent* AnimationComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | View | Shadow")
    UFakeShadowComponent* FakeShadowComponent{nullptr};

    // Unreal Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | View | Camera")
    UCameraComponent* CameraComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | View | Camera")
    USpringArmComponent* SpringArmComponent{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
    float SprintCameraFOV{100.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
    float SprintCameraInterpolationSpeed{5.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
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

    void BindDelegates();
};
