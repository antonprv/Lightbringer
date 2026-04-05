// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

// TODO: Redo all of this

#include "View/Actors/LBWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"

ALBWeaponBase::ALBWeaponBase()
{
    PrimaryActorTick.bCanEverTick = false;

    SkeletalMesh =
        CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");

    SetRootComponent(SkeletalMesh);

    SkeletalMesh->SetMassOverrideInKg(NAME_None, 1.5f);
    SkeletalMesh->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));

    SkeletalMesh->SetSimulatePhysics(true);
    
    SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    SkeletalMesh->SetCollisionObjectType(ECC_WorldDynamic);

    FCollisionResponseContainer CollisionContainer;
    CollisionContainer.Visibility = ECR_Block;
    CollisionContainer.Camera = ECR_Ignore;
    CollisionContainer.WorldStatic = ECR_Block;
    CollisionContainer.WorldDynamic = ECR_Block;
    CollisionContainer.Pawn = ECR_Block;
    CollisionContainer.PhysicsBody = ECR_Block;
    CollisionContainer.Vehicle = ECR_Block;
    CollisionContainer.Destructible = ECR_Block;

    SkeletalMesh->SetCollisionResponseToChannels(CollisionContainer);


}