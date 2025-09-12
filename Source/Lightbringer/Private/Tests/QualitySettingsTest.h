// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QualitySettingsTest.generated.h"

class UBoxComponent;

UCLASS()
class AQualitySettingsTest : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AQualitySettingsTest();

    UPROPERTY(VisibleAnywhere, Category = "Collision Component")
    UBoxComponent* BoxComponent;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor);
};
