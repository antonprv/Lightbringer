// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawnHub.generated.h"

UCLASS()
class AActorSpawnHub : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AActorSpawnHub();

    UPROPERTY(VisibleAnywhere, Category = "Spawn Settings")
    class USceneComponent* SpawnPoint{nullptr};

    UPROPERTY(EditAnywhere, Category = "Spawn Settings")
    TSubclassOf<AActor> ActorToSpawn{nullptr};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    class UBillboardComponent* SpawnPointMarker{nullptr};
};
