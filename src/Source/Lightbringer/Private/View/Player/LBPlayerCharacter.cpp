// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Player/LBPlayerCharacter.h"

#include "Engine/World.h"

#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "SkeletalMeshComponentBudgeted.h"
#include "DefaultMovementSet/CharacterMoverComponent.h"
#include "MotionWarpingComponent.h"
#include "GameFramework/GameplayCameraComponent.h"

// TEST
#include "Components/TextRenderComponent.h"
// TEST

#include "Components/FakeShadowComponent.h"

#include "Gameplay/Components/HealthComponent.h"
#include "Gameplay/Components/WeaponComponent.h"
#include "Gameplay/Subsystems/ComponentsDelegateMediator.h"

#include "View/Components/AnimUpdateRateOptimizationComponent.h"
#include "View/Player/PlayerDelegateMediator.h"
#include "View/Actors/LBWeaponBase.h"

#include "Data/Character/LBCharCameraTypes.h"
#include "Data/Character/LBCharMovementTypes.h"
#include "Data/Character/LBCharPropertiesForAnimation.h"
#include "Data/Character/LBCharPropertiesForCamera.h"
#include "Data/Character/LBCharPropertiesForTraversal.h"

DEFINE_LOG_CATEGORY_STATIC(LogALBPlayerCharacter, Log, Log)

/*
 * Class constructor
 */
ALBPlayerCharacter::ALBPlayerCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit/*
              .SetDefaultSubobjectClass<USkeletalMeshComponent>(
                  ACharacterBase::CharacterMeshName)
              .SetDefaultSubobjectClass<UActorComponent>(
                  ACharacterBase::AnimUpdateRateComponentName)*/)
{
    PrimaryActorTick.bCanEverTick = true;

    // Unreal Components
    Mesh->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
    Mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    Mesh->SetAutoCalculateSignificance(true);

    MotionWarping =
        CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarping");

    // Lightbringer Components
    HealthComponent =
        CreateDefaultSubobject<UHealthComponent>("Health Component");
    TextRenderComponent =
        CreateDefaultSubobject<UTextRenderComponent>("Health Text");
    TextRenderComponent->SetupAttachment(Capsule);

    TextRenderComponent->bOwnerNoSee = false;
    TextRenderComponent->SetReceivesDecals(false);

    FakeShadowComponent =
        CreateDefaultSubobject<UFakeShadowComponent>("Fake Shadow");
    FakeShadowComponent->SetupAttachment(Capsule);

    // FakeShadowComponent->ShadowRenderer->SetCaptureResolution(256);
    // FakeShadowComponent->ShadowRenderer->SetUpdateFrequency(30.0f);
    // FakeShadowComponent->ShadowRenderer->SetCaptureGamma(1.0f);

    // WeaponComponent =
    //     CreateDefaultSubobject<UWeaponComponent>("Weapon Component");
}

/*
 * Setup default values and perform checks
 */
void ALBPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (AnimUpdateRateComponent)
    {
        AnimUpdateRateComponent->DestroyComponent();
    }

    check(HealthComponent);
    check(TextRenderComponent);
    check(FakeShadowComponent);

    ComponentsDelegateMediator = UComponentsDelegateMediator::Get(GetWorld());

    // FakeShadowComponent->ShadowRenderer->ShowOnlyComponents.Add(
    //     WeaponComponent->WeaponActor->SkeletalMesh);
    // FakeShadowComponent->SetRelativeLocation(FVector(0.f, 0.f, -527.f));

    check(CharacterMover);
    check(ComponentsDelegateMediator);

    bIsMovementAllowed = true;

    BindDelegates();
}

void ALBPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // FRotator DesiredRotation = {
    //     -GetControlRotation().Pitch, GetControlRotation().Yaw + 180.f, 0.f};

    // TextRenderComponent->SetWorldRotation(DesiredRotation);
}

void ALBPlayerCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    HealthComponent->OnHealthChanged.RemoveAll(this);

    if (OnLanding.Contains(this,
            GET_FUNCTION_NAME_CHECKED(ALBPlayerCharacter, HandleLanding)))
    {
        OnLanding.RemoveDynamic(TObjectPtr<ALBPlayerCharacter>(this), &ALBPlayerCharacter::HandleLanding);
    }

    Super::EndPlay(EndPlayReason);
}

void ALBPlayerCharacter::BindDelegates()
{
    if (!ComponentsDelegateMediator->OnActorDeath.IsBoundToObject(this))
    {
        ComponentsDelegateMediator->OnActorDeath.AddUObject(
            TObjectPtr<ALBPlayerCharacter>(this), &ALBPlayerCharacter::HandleActorDeath);
    }

    if (!HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(
            TObjectPtr<ALBPlayerCharacter>(this), &ALBPlayerCharacter::DisplayHealth);
    }

    if (!OnLanding.Contains(this,
            GET_FUNCTION_NAME_CHECKED(ALBPlayerCharacter, HandleLanding)))
    {
        OnLanding.AddDynamic(TObjectPtr<ALBPlayerCharacter>(this), &ALBPlayerCharacter::HandleLanding);
    }
}

//====================================================
// Callback functions
//====================================================
void ALBPlayerCharacter::HandleDestruction(AActor* DestroyedActor)
{
    if (UPlayerDelegateMediator* DelegateMediator =
            UPlayerDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerDestruction(DestroyedActor);
    }
}

void ALBPlayerCharacter::HandleActorDeath(AActor* DeadActor)
{
    if (!GetWorld() || DeadActor != this) return;

    bUseControllerRotationYaw = false;

    bIsMovementAllowed = false;

    if (UPlayerDelegateMediator* DelegateMediator =
            UPlayerDelegateMediator::Get(GetWorld()))
    {
        DelegateMediator->DispatchPlayerDeath(this);
    }
}

void ALBPlayerCharacter::HandleLanding(
    const FHitResult& HitResult, const float& LandingSpeed)
{
    if (ComponentsDelegateMediator)
    {
        ComponentsDelegateMediator->DispatchPlayerJumpDamage(
            this, LandingSpeed, HitResult);
    }

    UE_LOG(LogALBPlayerCharacter, Display,
        TEXT("Jump velocity on landing: %f"), LandingSpeed);
}

//====================================================
// Debug HP
//====================================================
void ALBPlayerCharacter::DisplayHealth(const float& CurrentHealth)
{
    static float CachedHealth = -1.0f;
    if (!TextRenderComponent ||
        FMath::IsNearlyEqual(CachedHealth, CurrentHealth, 0.5f))
        return;

    CachedHealth = CurrentHealth;
    TextRenderComponent->SetText(
        FText::AsNumber(FMath::RoundToInt(CurrentHealth)));
}

//====================================================
// Getters
//====================================================
void ALBPlayerCharacter::GetMovementValues(
    float& OutForwardInput, float& OutRightInput)
{
    OutForwardInput = ForwardInput;
    OutRightInput = RightInput;
}

// ======================================================
// Controller Interfaces
// ======================================================
void ALBPlayerCharacter::MoveCustom_Implementation(const FVector2D Value)
{
    ForwardInput = bIsMovementAllowed ? Value.X : 0.f;
    RightInput = bIsMovementAllowed ? Value.Y : 0.f;
}

void ALBPlayerCharacter::PickUp_Implementation()
{
    // WeaponComponent -> Do pickup
}


// ======================================================
// Motion Matching Interfaces
// ======================================================
void ALBPlayerCharacter::SetCharacterInputState_Implementation(
    const FPlayerInputState& PlayerInputState)
{
    return;
}

void ALBPlayerCharacter::GetPropertiesForAnimation_Implementation(
    FLBCharPropertiesForAnimation& OutPropertiesForAnimation)
{
    return;
}

void ALBPlayerCharacter::GetPropertiesForCamera_Implementation(
    FLBCharPropertiesForCamera& OutPropertiesForCamera)
{
    return;
}

void ALBPlayerCharacter::GetPropertiesForTraversal_Implementation(
    FLBCharPropertiesForTraversal& OutPropertiesForTraversal)
{
    return;
}

// ======================================================
// Fake Shadow Interfaces
// ======================================================
void ALBPlayerCharacter::GetShadowCasterMesh_Implementation(
    USkeletalMeshComponent*& OutMesh)
{
    OutMesh = Mesh;
}
