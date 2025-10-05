// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Components/DecalComponent.h"
#include "BlobShadowComponent.generated.h"

class ACharacter;

class UMaterialInterface;

UCLASS()
class FAKESHADOW_API UBlobShadowComponent : public UDecalComponent
{
    GENERATED_BODY()

public:
    UBlobShadowComponent();

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDecalShadowDebugEnabled{false};
#endif

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
    float DecalTraceDistance{1000.f};

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY()
    ACharacter* CharacterOwner{nullptr};
    UPROPERTY()
    UMaterialInterface* BlobShadowMaterial{nullptr};

    bool bHasDecalHit{false};
    FHitResult DecalHitResult;
    FVector DecalStartHit{FVector::ZeroVector};
    FVector DecalEndHit{FVector::ZeroVector};
    void UpdateDecalTransform();
};
