// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Actors/LBWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"

ALBWeaponBase::ALBWeaponBase()
{
    PrimaryActorTick.bCanEverTick = false;

    SkeletalMesh =
        CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");

    SetRootComponent(SkeletalMesh);
}