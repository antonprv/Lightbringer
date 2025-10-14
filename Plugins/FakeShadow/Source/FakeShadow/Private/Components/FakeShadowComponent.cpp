// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "FakeShadowComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "Camera/CameraTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SkeletalMeshComponent.h"

#include "Materials/MaterialInterface.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"

#if WITH_EDITORONLY_DATA
#include "Components/ArrowComponent.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogUFakeShadowComponent, Log, Log)

const FVector UFakeShadowComponent::ShadowRendererDefaultLocation = {
    -750.f, 0.f, 0.f};
const FRotator UFakeShadowComponent::ShadowRendererDefaultRotation = {
    0.f, 0.f, -90.f};
const FVector UFakeShadowComponent::DefaultDecalSize{540.f, 300.f, 300.f};

UFakeShadowComponent::UFakeShadowComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    DecalSize = DefaultDecalSize;
    SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
}

void UFakeShadowComponent::BeginPlay()
{
    Super::BeginPlay();

    CharacterOwner = Cast<ACharacter>(GetOwner());
    check(CharacterOwner);

    ShadowRenderer->ShowOnlyComponents.Add(CharacterOwner->GetMesh());
}

void UFakeShadowComponent::OnRegister()
{
    Super::OnRegister();

    CreateShadowRenderer();
}

void UFakeShadowComponent::CreateShadowRenderer()
{
    ShadowRenderer = NewObject<USceneCaptureComponent2D>(this,
        USceneCaptureComponent2D::StaticClass(), NAME_None, RF_Transient);
    ShadowRenderer->SetupAttachment(this);
    ShadowRenderer->RegisterComponent();
    ShadowRenderer->SetRelativeLocationAndRotation(
        ShadowRendererDefaultLocation, ShadowRendererDefaultRotation);
    ShadowRenderer->bCaptureEveryFrame = true;
    ShadowRenderer->bCaptureOnMovement = true;
    ShadowRenderer->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;
    ShadowRenderer->PrimitiveRenderMode =
        ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
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
    FakeShadowMaterial = LoadObject<UMaterialInterface>(nullptr,
        TEXT(
            "MaterialInstanceConstant'/FakeShadow/Assets/Decals/Shadow/MI_DecalRenderTarget.MI_DecalRenderTarget'"));
    SetDecalMaterial(FakeShadowMaterial);

    FakeShadowTexture = LoadObject<UTextureRenderTarget2D>(nullptr,
        TEXT(
            "TextureRenderTarget2D'/FakeShadow/Assets/Decals/Shadow/Textures/ShadowRenderTarget.ShadowRenderTarget'"));

    ShadowRenderer->TextureTarget = FakeShadowTexture;
}
