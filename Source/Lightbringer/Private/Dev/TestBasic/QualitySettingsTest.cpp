// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "QualitySettingsTest.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "View/Rendering/GraphicsPresetManager.h"

DEFINE_LOG_CATEGORY_STATIC(QualitySettingsTest, Log, All)
// Sets default values
AQualitySettingsTest::AQualitySettingsTest()
{
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("Collision Box");
    RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AQualitySettingsTest::BeginPlay()
{
    Super::BeginPlay();
}

void AQualitySettingsTest::NotifyActorBeginOverlap(AActor* OtherActor)
{
    if (BoxComponent && OtherActor)
    {
        if (UGraphicsPresetManager* GraphicsPresetManager =
                UGraphicsPresetManager::Get())
        {
            if (GraphicsPresetManager->IsAtLowQuality())
            {
                UE_LOG(QualitySettingsTest, Display,
                    TEXT("Graphics quality is set to low"))

#if WITH_EDITORONLY_DATA
                GEngine->AddOnScreenDebugMessage(-1, 3.f,  //
                    FColor::Magenta,                       //
                    "Graphics quality is set to low",      //
                    false, FVector2D(3.f, 3.f));
#endif
            }
        }
    }
}
