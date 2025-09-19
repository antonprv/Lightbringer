// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LBDevDamageActor.generated.h"

class USceneComponent;
class USphereComponent;
class UDamageType;

UCLASS()
class LIGHTBRINGER_API ALBDevDamageActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ALBDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent{nullptr};

    UPROPERTY(VisibleAnywhere)
    class UBillboardComponent* Billboard;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float Radius{150.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float Damage{10.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    bool bDoFullDamage{false};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    FColor Color{FColor::Magenta};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITORONLY_DATA
    virtual void PostEditChangeProperty(
        FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY()
    USphereComponent* PreviewSphere;

    void UpdateSphereRadius();
    void UpdateSphereColor();
};
