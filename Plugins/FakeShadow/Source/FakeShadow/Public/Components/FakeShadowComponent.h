// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Components/DecalComponent.h"
#include "FakeShadowComponent.generated.h"

class ACharacter;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

#if WITH_EDITORONLY_DATA
class UArrowComponent;
#endif

class UMaterialInterface;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FAKESHADOW_API UFakeShadowComponent : public UDecalComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UFakeShadowComponent();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneCaptureComponent2D* ShadowRenderer{nullptr};

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    static const FVector ShadowRendererDefaultLocation;
    static const FRotator ShadowRendererDefaultRotation;
    static const FVector DefaultDecalSize;

#if WITH_EDITORONLY_DATA
    UPROPERTY()
    UArrowComponent* CameraArrow{nullptr};
#endif

    UPROPERTY()
    ACharacter* CharacterOwner{nullptr};
    UPROPERTY()
    UMaterialInterface* FakeShadowMaterial{nullptr};
    UPROPERTY()
    UTextureRenderTarget2D* FakeShadowTexture{nullptr};

    void CreateShadowRenderer();
    void AssignMaterials();
};
