// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LBWeaponBase.generated.h"

class USkeletalMeshComponent;

UCLASS()
class LIGHTBRINGER_API ALBWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    ALBWeaponBase();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMesh{nullptr};
};
