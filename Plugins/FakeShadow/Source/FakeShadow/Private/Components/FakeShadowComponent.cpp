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
    -10000.f, 0.f, 0.f};
const FRotator UFakeShadowComponent::ShadowRendererDefaultRotation = {
    0.f, 0.f, -90.f};
const FVector UFakeShadowComponent::DefaultDecalSize{540.f, 300.f, 300.f};

UFakeShadowComponent::UFakeShadowComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    DecalSize = DefaultDecalSize;
    SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

    ShadowRenderer =
        CreateDefaultSubobject<USceneCaptureComponent2D>("Shadow Renderer");
    ShadowRenderer->SetupAttachment(this);
    ShadowRenderer->SetRelativeLocationAndRotation(
        ShadowRendererDefaultLocation, ShadowRendererDefaultRotation);
    ShadowRenderer->bCaptureEveryFrame = true;
    ShadowRenderer->bCaptureOnMovement = true;
    ShadowRenderer->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;
    ShadowRenderer->PrimitiveRenderMode =
        ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
    ShadowRenderer->ProjectionType = ECameraProjectionMode::Orthographic;
    ShadowRenderer->OrthoWidth = 465.f;

#if WITH_EDITORONLY_DATA
    CameraArrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(
        TEXT("Camera Arrow"));
    if (CameraArrow)
    {
        CameraArrow->ArrowColor = FColor(150, 200, 255);
        CameraArrow->bTreatAsASprite = true;
        CameraArrow->SetupAttachment(ShadowRenderer);
        CameraArrow->bIsScreenSizeScaled = true;
        CameraArrow->SetHiddenInGame(false);
    }
#endif

    FakeShadowMaterial = LoadObject<UMaterialInterface>(nullptr,
        TEXT(
            "MaterialInstanceConstant'/FakeShadow/Assets/Decals/Shadow/MI_DecalRenderTarget.MI_DecalRenderTarget'"));
    SetDecalMaterial(FakeShadowMaterial);

    FakeShadowTexture = LoadObject<UTextureRenderTarget2D>(nullptr,
        TEXT(
            "TextureRenderTarget2D'/FakeShadow/Assets/Decals/Shadow/Textures/ShadowRenderTarget.ShadowRenderTarget'"));

    ShadowRenderer->TextureTarget = FakeShadowTexture;
}

void UFakeShadowComponent::BeginPlay()
{
    Super::BeginPlay();

    CharacterOwner = Cast<ACharacter>(GetOwner());

    check(CharacterOwner);

    ShadowRenderer->ShowOnlyComponent(CharacterOwner->GetMesh());
}
