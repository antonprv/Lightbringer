// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBDevDamageActor.h"

#include "GameFramework/DamageType.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"

#if WITH_EDITORONLY_DATA

#include "DrawDebugHelpers.h"
#include "Components/BillboardComponent.h"

#endif

// Sets default values
ALBDevDamageActor::ALBDevDamageActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 1 / 30.f;

    SceneComponent =
        CreateDefaultSubobject<USceneComponent>("Actor Transform");
    SetRootComponent(SceneComponent);
    SceneComponent->SetMobility(EComponentMobility::Movable);

    PreviewSphere = CreateDefaultSubobject<USphereComponent>("PreviewSphere");
    PreviewSphere->SetupAttachment(GetRootComponent());

#if WITH_EDITORONLY_DATA
    Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
    Billboard->SetupAttachment(SceneComponent);
    static ConstructorHelpers::FObjectFinderOptional<UTexture2D> SpriteFinder(
        TEXT("/Engine/EditorResources/S_Note.S_Note"));
    if (SpriteFinder.Succeeded())
    {
        Billboard->SetSprite(SpriteFinder.Get());
    }
#endif
}

// Called when the game starts or when spawned
void ALBDevDamageActor::BeginPlay()
{
    Super::BeginPlay();

#if WITH_EDITOR
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, Color, true);
#endif
}

void ALBDevDamageActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (!HasAnyFlags(RF_ClassDefaultObject))
    {
        PreviewSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        PreviewSphere->SetHiddenInGame(true);
        PreviewSphere->SetMobility(EComponentMobility::Movable);
    }

    UpdateSphereRadius();
    UpdateSphereColor();
}

#if WITH_EDITOR
void ALBDevDamageActor::PostEditChangeProperty(
    FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    UpdateSphereRadius();
    UpdateSphereColor();
}
#endif

// Called every frame
void ALBDevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IsOverlappingActor(nullptr))
    {
        UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage,
            GetActorLocation(), Radius, nullptr, {}, this, nullptr,
            bDoFullDamage);
    }
}

void ALBDevDamageActor::UpdateSphereRadius()
{
    if (PreviewSphere)
    {
        PreviewSphere->SetSphereRadius(Radius);
    }
}

void ALBDevDamageActor::UpdateSphereColor()
{
    if (PreviewSphere)
    {
        PreviewSphere->ShapeColor = Color;
    }
}
