// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnToggle.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FSpawnTrigger, AActor*);

UCLASS() class ASpawnToggle : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASpawnToggle();

    FSpawnTrigger OnSpawnTriggered;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* BoxComponent{nullptr};

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
