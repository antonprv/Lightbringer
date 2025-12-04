// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Dev/TestBasic/PhysicsTest.h"

#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY_STATIC(APhysicsTestLog, Log, Log)
// Sets default values
APhysicsTest::APhysicsTest()
{
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
    SetRootComponent(StaticMesh);

    UStaticMesh* Mesh = LoadObject<UStaticMesh>(
        nullptr, TEXT("StaticMesh'/Game/Assets/Meshes/Test/Sphere.Sphere'"));
    if (Mesh)
    {
        StaticMesh->SetStaticMesh(Mesh);
    }
    else
    {
        UE_LOG(APhysicsTestLog, Warning,
            TEXT("Static Mesh not found, set to None"))
    }
}

// Called when the game starts or when spawned
void APhysicsTest::BeginPlay()
{
    Super::BeginPlay();

    StaticMesh->SetSimulatePhysics(true);
    StaticMesh->SetLinearDamping(.1f);
    StaticMesh->SetAngularDamping(.1f);
    StaticMesh->SetMassOverrideInKg(NAME_None, 1.f);

    MaterialInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

    FMaterialParameterInfo MaterialParameterInfo;
    MaterialParameterInfo.Name = "BaseColor";
    MaterialInstance->GetVectorParameterValue(
        MaterialParameterInfo, DefaultColor);
}

void APhysicsTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetWorldTimerManager().ClearTimer(ColorTimer);

    Super::EndPlay(EndPlayReason);
}

void APhysicsTest::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other,
    UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
    FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation,
        HitNormal, NormalImpulse, Hit);

    MaterialInstance->SetVectorParameterValue("BaseColor", HitColor);

    GetWorldTimerManager().SetTimer(
        ColorTimer, this, &APhysicsTest::ResetColor, 0.01f);

    StaticMesh->AddImpulse(HitNormal);
}

void APhysicsTest::ResetColor()
{
    MaterialInstance->SetVectorParameterValue("BaseColor", DefaultColor);
}
