// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerControllable.h"
#include "Interfaces/ShadowCaster.h"
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

class UTrajectoryGenerator;
class UTrajectoryErrorWarping;

UCLASS()
class LIGHTBRINGER_API ALBPlayerCharacter : public ACharacter,
                                            public IPlayerControllable,
                                            public IShadowCaster
{
    GENERATED_BODY()

public:
    //=============================================
    // My custom components
    //=============================================
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | Gameplay | Other")
    ULBCharacterMovementComponent* MovementHandlerComponent{nullptr};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | Gameplay | Other")
    UWeaponComponent* WeaponComponent{nullptr};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | View | Animation")
    UAnimationComponent* AnimationComponent{nullptr};

    //=============================================
    // My custom components parameters
    //=============================================
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
    float SprintCameraFOV{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
    float SlideCameraFOV{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
    float JumpCameraFOV{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
    float SprintCameraInterpolationSpeed{0.f};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,
        Category = "Components | View | Camera")
    float SprintRightCameraInterpolationSpeed{0.f};

    //=============================================
    // Unreal components
    //=============================================
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
        Category = "Components | Gameplay | Health")
    UHealthComponent* HealthComponent{nullptr};

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite,
        Category = "Components | Gameplay | Health")
    UTextRenderComponent* TextRenderComponent{nullptr};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | View | Camera")
    UCameraComponent* CameraComponent{nullptr};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
        Category = "Components | View | Camera")
    USpringArmComponent* SpringArmComponent{nullptr};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
    virtual void Jump() override;

public:
    ALBPlayerCharacter(const FObjectInitializer& ObjInit);

    // IControllable
    virtual void MoveCustom_Implementation(const FVector2D Value) override;
    virtual void LookCustom_Implementation(const FVector2D Value) override;
    virtual void JumpCustom_Implementation() override;
    virtual void SprintCustom_Implementation(
        const bool bWantsToSprint) override;
    virtual void SprintToggleCustom_Implementation() override;
    virtual void CrouchCustom_Implementation(
        const bool bWantsToCrouch) override;
    virtual void CrouchToggleCustom_Implementation() override;
    virtual void WalkCustom_Implementation(const bool bWantsToWalk) override;
    virtual void WalkToggleCustom_Implementation() override;
    virtual void AimCustom_Implementation(const bool bWantsToAim) override;
    virtual void PickCustom_Implementation() override;

    // IShadowCaster
    virtual void GetShadowCasterMesh_Implementation(
        USkeletalMeshComponent*& OutMesh) override;

private:
    UPROPERTY()
    UComponentsDelegateMediator* ComponentsDelegateMediator{nullptr};

    float CurrentCameraFOV{0.f};
    float DefaultCameraFOV{0.f};

    float CurrentSocketRightOffset{0.f};
    float DefaultSocketRightOffset{0.f};

    float DefaultSprintRightCameraInterpolationSpeed{0.f};

    bool bWalkToggle{false};
    bool bSprintToggle{false};
    bool bCrouchToggle{false};

    void HandleActorDeath(AActor* DeadActor);
    void OnHealthChanged(float CurrentHealth);

    void InterpolateCamera(const float& DeltaSeconds);
    void InterpolateSprintRightCamera(const float& DeltaSeconds);
    void DisplayText(const float& CurrentHealth);

    UFUNCTION()
    void OnGroundLanding(const FHitResult& Hit);

    UFUNCTION()
    void HandleDestruction(AActor* DestroyedActor);

    void BindDelegates();
};
