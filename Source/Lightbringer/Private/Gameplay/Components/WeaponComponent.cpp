// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Components/WeaponComponent.h"
#include "LBWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogUWeaponComponent, Log, Log)

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CharacterOwner = Cast<ACharacter>(GetOwner());

    SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon()
{
    if (!GetWorld() || !CharacterOwner || !WeaponClass) return;

    FTransform SpawnTransform =
        CharacterOwner->GetMesh()->GetSocketTransform(FName("WeaponSocket"));

    WeaponActor = GetWorld()->SpawnActorDeferred<ALBWeaponBase>(WeaponClass,
        SpawnTransform, CharacterOwner, CharacterOwner->GetInstigator());

    if (!WeaponActor)
    {
        UE_LOG(LogUWeaponComponent, Error, TEXT("Spawn failed"));
        return;
    }

    WeaponActor->FinishSpawning(SpawnTransform);

    if (WeaponActor->SkeletalMesh && CharacterOwner->GetMesh())
    {
        WeaponActor->SkeletalMesh->AttachToComponent(CharacterOwner->GetMesh(),
            FAttachmentTransformRules::SnapToTargetNotIncludingScale,
            TEXT("WeaponSocket"));
    }
}

void UWeaponComponent::UpdateLeftHandRotation()
{
    if (!GetWorld() || !CharacterOwner || !WeaponActor) return;

    WeaponLeftHandSocketRotation =
        WeaponActor->SkeletalMesh->GetSocketRotation(FName("LeftHandSocket"));
}

void UWeaponComponent::UpdateLeftHandLocation()
{
    if (!GetWorld() || !CharacterOwner || !WeaponActor) return;

    WeaponLeftHandSocketLocation =
        WeaponActor->SkeletalMesh->GetSocketLocation(FName("LeftHandSocket"));
}