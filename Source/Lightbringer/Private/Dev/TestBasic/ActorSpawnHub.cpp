// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Dev/TestBasic/ActorSpawnHub.h"

#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnToggle.h"
#include "Engine/Engine.h"

#if WITH_EDITORONLY_DATA
#include "Components/BillboardComponent.h"
#endif

#include "Dev/TestBasic/PhysicsTest.h"

DEFINE_LOG_CATEGORY_STATIC(AActorSpawnHubLog, Log, Log)

class ASpawnToggle;

AActorSpawnHub::AActorSpawnHub()
{
    PrimaryActorTick.bCanEverTick = false;

    ActorToSpawn = APhysicsTest::StaticClass();  // Spawn Test Actor by default

    SpawnPoint = CreateDefaultSubobject<USceneComponent>("Actor Spawn Point");
    SetRootComponent(SpawnPoint);

#if WITH_EDITORONLY_DATA
    SpawnPointMarker =
        CreateDefaultSubobject<UBillboardComponent>("Actor Spawn Billboard");
    SpawnPointMarker->SetupAttachment(SpawnPoint);

    // Load default sprite from engine's Paper2D plugin
    UTexture2D* Sprite = LoadObject<UTexture2D>(nullptr,  //
        TEXT("Texture2D'/Engine/Tutorial/Paper2D/TutorialAssets/"
             "Paper2DSprite_TutorialIcon.Paper2DSprite_TutorialIcon'"));
    if (Sprite)
    {
        SpawnPointMarker->SetSprite(Sprite);
    }
    else
    {
        UE_LOG(AActorSpawnHubLog, Warning,
            TEXT("Coul not load default sprite, set to None"))
    }
#endif
}

// Called when the game starts or when spawned
void AActorSpawnHub::BeginPlay()
{
    Super::BeginPlay();

    SpawnWithActorInfo(nullptr);

    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::GetAllActorsOfClass(
            World, ASpawnToggle::StaticClass(), ToggleActors);

        if (ToggleActors.Num() > 0)
        {
            for (AActor* Actor : ToggleActors)
            {
                if (ASpawnToggle* Toggle = Cast<ASpawnToggle>(Actor))
                {
                    Toggle->OnSpawnTriggered.AddUObject(
                        this, &AActorSpawnHub::SpawnWithActorInfo);
                }
            }
        }
    }
}

void AActorSpawnHub::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (ToggleActors.Num() > 0)
    {
        for (AActor* Actor : ToggleActors)
        {
            if (ASpawnToggle* Toggle = Cast<ASpawnToggle>(Actor))
            {
                if (Toggle->OnSpawnTriggered.IsBound())
                {
                    Toggle->OnSpawnTriggered.RemoveAll(this);
                }
            }
        }
    }

    Super::EndPlay(EndPlayReason);
}

void AActorSpawnHub::SpawnWithActorInfo(AActor* Actor)
{
    if (UWorld* World = GetWorld())
    {
        World->SpawnActor(ActorToSpawn, &SpawnPoint->GetComponentTransform());

        if (Actor)
        {
            UE_LOG(AActorSpawnHubLog, Display, TEXT("Spawn triggered by %s"),
                *Actor->GetName())
#if WITH_EDITORONLY_DATA
            FString Message = FString::Printf(
                TEXT("Spawn triggered by %s"), *Actor->GetName());
            GEngine->AddOnScreenDebugMessage(
                -1, 3.f, FColor::Blue, Message, false, FVector2D(2.f, 2.f));
#endif
        }
    }
}
