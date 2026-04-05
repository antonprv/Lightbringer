// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

// TODO: Redo all of this

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "WeaponComponent.generated.h"

class USphereComponent;
class ALBWeaponBase;
class ACharacterBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIGHTBRINGER_API UWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UWeaponComponent();

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

    UPROPERTY()
    ALBWeaponBase* WeaponActor{nullptr};
    
    void PickupWeapon();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ACharacterBase* CharacterOwner{nullptr};
    UPROPERTY()
    USphereComponent* WeaponTraceSphere{nullptr};

    bool bHasWeapon{false};
    bool bCanPickupWeapon{false};

    FVector WeaponLeftHandSocketLocation{FVector::ZeroVector};
    FRotator WeaponLeftHandSocketRotation{FRotator::ZeroRotator};

    void UpdateLeftHandLocation();
    void UpdateLeftHandRotation();

    UFUNCTION()
    void HandleWeaponTraceOverlap(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void CheckDistanceToWeapon(AActor* WeaponToPick);
};
