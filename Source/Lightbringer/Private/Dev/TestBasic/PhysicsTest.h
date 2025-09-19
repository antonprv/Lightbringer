// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsTest.generated.h"

UCLASS()
class APhysicsTest : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APhysicsTest();

    UPROPERTY(EditAnywhere)
    class UStaticMeshComponent* StaticMesh{nullptr};

    UPROPERTY(EditAnywhere)
    FLinearColor HitColor{FLinearColor::Red};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other,
        class UPrimitiveComponent* OtherComp, bool bSelfMoved,
        FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
        const FHitResult& Hit);

private:
    class UMaterialInstanceDynamic* MaterialInstance{nullptr};
    FTimerHandle ColorTimer;
    FLinearColor DefaultColor{FLinearColor::Black};
    void ResetColor();
};
