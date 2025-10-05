// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ALBWeaponBase;
class ACharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIGHTBRINGER_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UWeaponComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ALBWeaponBase> WeaponClass{nullptr};

    // Socket info getters
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
    FVector GetWeaponLeftHandSocketLocation()
    {
        UpdateLeftHandLocation();
        return WeaponLeftHandSocketLocation;
    };
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
    FRotator GetWeaponLeftHandSocketRotation()
    {
        UpdateLeftHandRotation();
        return WeaponLeftHandSocketRotation;
    };

private:
    UPROPERTY()
    ALBWeaponBase* WeaponActor{nullptr};
    UPROPERTY()
    ACharacter* CharacterOwner{nullptr};
    FVector WeaponLeftHandSocketLocation{FVector::ZeroVector};
    FRotator WeaponLeftHandSocketRotation{FRotator::ZeroRotator};

    void SpawnWeapon();
    void UpdateLeftHandLocation();
    void UpdateLeftHandRotation();
};
