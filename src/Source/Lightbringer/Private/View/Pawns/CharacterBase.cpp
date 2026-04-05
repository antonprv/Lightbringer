// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Pawns/CharacterBase.h"

// Essential unreal components
#include "Components/CapsuleComponent.h"
#include "SkeletalMeshComponentBudgeted.h"
#include "DefaultMovementSet/CharacterMoverComponent.h"

// Essential unreal camera components
#include "GameFramework/GameplayCameraComponent.h"

// Controller components
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

// Generic unreal stuff
#include "Engine/World.h"

// Lightbringer components
#include "View/Components/AnimUpdateRateOptimizationComponent.h"

/*
* Constants for easier class swaps in child constructors
*/
FName ACharacterBase::CharacterMeshName("Mesh");
FName ACharacterBase::MoverComponentName("CharacterMover");
FName ACharacterBase::AnimUpdateRateComponentName("AnimUpdateRateComponent");

/*
 * Class constructor
 */
ACharacterBase::ACharacterBase(const FObjectInitializer& ObjInit)
{
    PrimaryActorTick.bCanEverTick = true;
    SetTickGroup(TG_PrePhysics);

    // Compatability with Mover
    bReplicates = false;
    SetReplicateMovement(false);

    // Unreal Components
    Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
    Capsule->SetupAttachment(GetRootComponent());
    Capsule->SetCapsuleHalfHeight(86.f);
    Capsule->SetCapsuleRadius(30.f);
    Capsule->SetLineThickness(0.5f);
    Capsule->SetCollisionProfileName(TEXT("Pawn"));
    Capsule->SetTickGroup(TG_DuringPhysics);
    Capsule->PrimaryComponentTick.bStartWithTickEnabled = true;
    Capsule->SetComponentTickInterval(0.0125f);

    Mesh = CreateDefaultSubobject<USkeletalMeshComponentBudgeted>(
        "Mesh");
    Mesh->SetupAttachment(Capsule);
    Mesh->SetWorldTransform(FTransform::Identity);
    Mesh->SetTickGroup(TG_PrePhysics);
    Mesh->PrimaryComponentTick.bStartWithTickEnabled = false;
    Mesh->SetComponentTickInterval(0.01f);
    Mesh->VisibilityBasedAnimTickOption =
        EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;

    GameplayCamera =
        CreateDefaultSubobject<UGameplayCameraComponent>("GameplayCamera");
    GameplayCamera->SetupAttachment(Mesh);
    GameplayCamera->SetTickGroup(TG_PostPhysics);
    GameplayCamera->PrimaryComponentTick.bStartWithTickEnabled = false;
    GameplayCamera->SetComponentTickInterval(0.01f);

    CharacterMover =
        CreateDefaultSubobject<UCharacterMoverComponent>("CharacterMover");
    CharacterMover->SetTickGroup(TG_PrePhysics);
    CharacterMover->PrimaryComponentTick.bStartWithTickEnabled = false;
    CharacterMover->SetComponentTickInterval(0.01f);

    AnimUpdateRateComponent =
        CreateOptionalDefaultSubobject<UAnimUpdateRateOptimizationComponent>(
            "Anim Update Rate Optimization Component");
}

bool ACharacterBase::IsControlledByPlayer()
{
    if (APlayerController* PlayerController =
            Cast<APlayerController>(GetController()))
    {
        return true;
    }
    return false;
}

void ACharacterBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const bool bIsFalling = CharacterMover->IsFalling();
    const bool bIsGrounded = CharacterMover->IsOnGround();

    if (!bIsGrounded)
    {
        JumpVelocity = -CharacterMover->GetVelocity().Z;
    }

    if (bWasFalling && bIsGrounded)
    {
        ResolveGroundHit();
        OnLanding.Broadcast(GroundHit, JumpVelocity);
    }

    bWasFalling = bIsFalling;
}

void ACharacterBase::ResolveGroundHit()
{
    // Пропускаем трейс при малых прыжках (менее 150 юнитов/сек)
    if (JumpVelocity < 150.0f)
    {
        GroundHit = FHitResult();
        return;
    }

    const FVector Start = GetActorLocation();
    const FVector End = Start - FVector(0.f, 0.f, 200.f);
    FCollisionQueryParams Params(SCENE_QUERY_STAT(LandingTrace), false, this);
    GetWorld()->LineTraceSingleByChannel(
        GroundHit, Start, End, ECC_WorldStatic, Params);
}

/*
 * Getters
 */
USkeletalMeshComponentBudgeted* ACharacterBase::GetMesh() const
{
    return Mesh;
}

UCharacterMoverComponent* ACharacterBase::GetCharacterMovement() const
{
    return CharacterMover;
}