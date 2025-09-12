// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "SpawnToggle.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnToggle::ASpawnToggle()
{
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
    BoxComponent->SetHiddenInGame(false);
    SetRootComponent(BoxComponent);
}

void ASpawnToggle::NotifyActorBeginOverlap(AActor* OtherActor)
{
    if (OtherActor)
    {
        OnSpawnTriggered.Broadcast(OtherActor);
    }
}
