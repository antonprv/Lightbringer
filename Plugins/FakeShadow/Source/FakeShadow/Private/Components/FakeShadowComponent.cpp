// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Components/FakeShadowComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"

#include "Materials/MaterialInterface.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"

#include "Kismet/KismetRenderingLibrary.h"
#include "UObject/SoftObjectPath.h"

#if WITH_EDITORONLY_DATA
#include "Components/ArrowComponent.h"
#endif

#include "Interfaces/ShadowCaster.h"

DEFINE_LOG_CATEGORY_STATIC(LogUFakeShadowComponent, Log, Log)

const FVector UFakeShadowComponent::ShadowRendererDefaultLocation = {
    -750.f, 0.f, 0.f};
const FRotator UFakeShadowComponent::ShadowRendererDefaultRotation = {
    0.f, 0.f, -90.f};
const FVector UFakeShadowComponent::DefaultDecalSize{540.f, 300.f, 300.f};

UFakeShadowComponent::UFakeShadowComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    DecalSize = DefaultDecalSize;
    SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

    // === Load assets in constructor so they are included in cook ===
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> Mat(TEXT(
        "/FakeShadow/Assets/Decals/Instances/MI_DecalRenderTarget.MI_DecalRenderTarget"));
    static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RT(TEXT(
        "/FakeShadow/Assets/RenderTargets/RT_Shadow.RT_Shadow"));

    if (ensureMsgf(Mat.Succeeded(),
            TEXT("Failed to find %s (%s)."),
            *FakeShadowMaterial->GetName(),
            *FakeShadowMaterial->GetClass()->GetName()))
    {
        FakeShadowMaterial = Mat.Object;
    }

    if (ensureMsgf(RT.Succeeded(),
            TEXT("Failed to find %s (%s)."),
            *FakeShadowTexture->GetName(),
            *FakeShadowTexture->GetClass()->GetName()))
    {
        FakeShadowTexture = RT.Object;
    }
}

void UFakeShadowComponent::BeginPlay()
{
    Super::BeginPlay();

    ShadowOwner = Cast<APawn>(GetOwner());

    checkf(
        ShadowOwner, TEXT("Fatal error: invalid %s"), *ShadowOwner->GetName());

    USkeletalMeshComponent* ShadowMesh = nullptr;
    GetShadowMesh(ShadowMesh);

    checkf(ShadowMesh,
        TEXT("Fatal error: expected %s, but got nullptr instead"),
        *ShadowMesh->GetName());

    ShadowRenderer->ShowOnlyComponents.Add(ShadowMesh);
}

void UFakeShadowComponent::OnRegister()
{
    Super::OnRegister();

    CreateShadowRenderer();
}

void UFakeShadowComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (FakeShadowTexture)
    {
        UKismetRenderingLibrary::ClearRenderTarget2D(
            this, FakeShadowTexture, FLinearColor::Transparent);
    }

    ShadowRenderer->CaptureScene();
}

void UFakeShadowComponent::CreateShadowRenderer()
{
    ShadowRenderer = NewObject<USceneCaptureComponent2D>(this,
        USceneCaptureComponent2D::StaticClass(), NAME_None, RF_Transient);
    ShadowRenderer->SetupAttachment(this);
    ShadowRenderer->RegisterComponent();
    ShadowRenderer->SetRelativeLocationAndRotation(
        ShadowRendererDefaultLocation, ShadowRendererDefaultRotation);
    ShadowRenderer->bCaptureEveryFrame = false;
    ShadowRenderer->bCaptureOnMovement = false;
    ShadowRenderer->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;
    ShadowRenderer->PrimitiveRenderMode =
        ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
    ShadowRenderer->ShowFlags.Game = false;
    ShadowRenderer->ShowFlags.Lighting = false;
    ShadowRenderer->ProjectionType = ECameraProjectionMode::Orthographic;
    ShadowRenderer->OrthoWidth = 500.f;

#if WITH_EDITORONLY_DATA
    CameraArrow = NewObject<UArrowComponent>(
        this, UArrowComponent::StaticClass(), NAME_None, RF_Transient);
    CameraArrow->SetupAttachment(ShadowRenderer);
    CameraArrow->RegisterComponent();
    if (CameraArrow)
    {
        CameraArrow->ArrowColor = FColor(150, 200, 255);
        CameraArrow->bTreatAsASprite = true;
        CameraArrow->bIsScreenSizeScaled = true;
        CameraArrow->SetHiddenInGame(false);
    }
#endif

    AssignMaterials();
}

void UFakeShadowComponent::AssignMaterials()
{
    SetDecalMaterial(FakeShadowMaterial);
    ShadowRenderer->TextureTarget = FakeShadowTexture;
}

void UFakeShadowComponent::GetShadowMesh(USkeletalMeshComponent*& ShadowMesh) 
{
    if (!ShadowOwner) return;

    if (!ensureMsgf(ShadowOwner->GetClass()->ImplementsInterface(
                        UShadowCaster::StaticClass()),
            TEXT("%s (%s) does not implement interface %s"),
            *ShadowOwner->GetName(), *ShadowOwner->GetClass()->GetName(),
            *UShadowCaster::StaticClass()->GetName()))
    {
        return;
    }

    IShadowCaster::Execute_GetShadowCasterMesh(ShadowOwner, ShadowMesh);
}