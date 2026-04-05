// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

// TODO: Redo all of this

#include "Gameplay/Components/WeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/Character.h"
#include "Engine/World.h"

#include "View/Actors/LBWeaponBase.h"
#include "View/Pawns/CharacterBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogUWeaponComponent, Log, Log)

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    //WeaponTraceSphere =
    //    CreateDefaultSubobject<USphereComponent>("Weapon Trace Sphere");
    //WeaponTraceSphere->SetupAttachment(CharacterOwner->GetRootComponent());
    //WeaponTraceSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    //WeaponTraceSphere->SetCollisionObjectType(ECC_WorldDynamic);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    //CharacterOwner = Cast<ACharacterBase>(GetOwner());
    //check(CharacterOwner);

    //if (!WeaponTraceSphere->OnComponentBeginOverlap.Contains(
    //        this, GET_FUNCTION_NAME_CHECKED(
    //                  UWeaponComponent, HandleWeaponTraceOverlap)))
    //{
    //    WeaponTraceSphere->OnComponentBeginOverlap.AddDynamic(
    //        this, &UWeaponComponent::HandleWeaponTraceOverlap);
    //}
}

void UWeaponComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    if (WeaponTraceSphere->OnComponentBeginOverlap.Contains(
            this, GET_FUNCTION_NAME_CHECKED(
                      UWeaponComponent, HandleWeaponTraceOverlap)))
    {
        WeaponTraceSphere->OnComponentBeginOverlap.RemoveDynamic(
            this, &UWeaponComponent::HandleWeaponTraceOverlap);
    }

    Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::HandleWeaponTraceOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!OtherActor) return;

    if (OtherActor->GetClass()->IsChildOf(ALBWeaponBase::StaticClass()))
    {
        CheckDistanceToWeapon(OtherActor);
    }
}

void UWeaponComponent::CheckDistanceToWeapon(AActor* WeaponToPick)
{
    // FVector::Distance(
    //     WeaponToPick->GetActorLocation(),
    //     CharacterOwner->GetActorLocation());
}

void UWeaponComponent::PickupWeapon()
{
    if (bHasWeapon || !bCanPickupWeapon) return;
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