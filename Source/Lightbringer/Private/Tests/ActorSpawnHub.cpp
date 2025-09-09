// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#include "ActorSpawnHub.h"
#include "PhysicsTest.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"

#if WITH_EDITORONLY_DATA
#include "Components/BillboardComponent.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(AActorSpawnHubLog, Log, Log)

AActorSpawnHub::AActorSpawnHub()
{
    PrimaryActorTick.bCanEverTick = false;

    ActorToSpawn = APhysicsTest::StaticClass();  // Spawn Test Actor by default

    SpawnPoint = CreateDefaultSubobject<USceneComponent>("Actor Spawn Point");
    SetRootComponent(SpawnPoint);

#if WITH_EDITORONLY_DATA
    SpawnPointMarker = CreateDefaultSubobject<UBillboardComponent>("Actor Spawn Billboard");
    SpawnPointMarker->SetupAttachment(SpawnPoint);

    // Load default sprite from engine's Paper2D plugin
    UTexture2D* Sprite = LoadObject<UTexture2D>(nullptr,  //
        TEXT("Texture2D'/Engine/Tutorial/Paper2D/TutorialAssets/Paper2DSprite_TutorialIcon.Paper2DSprite_TutorialIcon'"));
    if (Sprite)
    {
        SpawnPointMarker->SetSprite(Sprite);
    }
    else
    {
        UE_LOG(AActorSpawnHubLog, Warning, TEXT("Coul not load default sprite, set to None"))
    }
#endif
}

// Called when the game starts or when spawned
void AActorSpawnHub::BeginPlay()
{
    Super::BeginPlay();

    if (UWorld* World = GetWorld())
    {

        World->SpawnActor(ActorToSpawn, &SpawnPoint->GetComponentTransform());
    }
}