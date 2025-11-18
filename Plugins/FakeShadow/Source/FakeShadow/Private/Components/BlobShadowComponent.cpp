// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Components/BlobShadowComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Materials/MaterialInterface.h"

#if WITH_EDITORONLY_DATA
#include "DrawDebugHelpers.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogUBlobShadowComponent, Log, Log)

UBlobShadowComponent::UBlobShadowComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    BlobShadowMaterial = LoadObject<UMaterialInterface>(nullptr,
        TEXT(
            "MaterialInstanceConstant'/FakeShadow/Assets/Decals/Shadow/MI_Decal.MI_Decal'"));

    SetDecalMaterial(BlobShadowMaterial);
}

void UBlobShadowComponent::BeginPlay()
{
    Super::BeginPlay();

    CharacterOwner = Cast<ACharacter>(GetOwner());

    SetRelativeLocation(FVector(0.f, 0.f,
        -CharacterOwner->GetCapsuleComponent()
            ->GetScaledCapsuleHalfHeight()));  // bottom of the capsule
    SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

    UpdateDecalTransform();
}

// Called every frame
void UBlobShadowComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdateDecalTransform();
}

void UBlobShadowComponent::UpdateDecalTransform()
{
    if (!GetWorld() || !GetOwner()) return;

    if (CharacterOwner)
    {
        DecalStartHit =
            CharacterOwner->GetMesh()->GetSocketLocation(FName("DecalRoot"));

        if (DecalStartHit == FVector::ZeroVector)
        {
            UE_LOG(LogUBlobShadowComponent, Warning,
                TEXT(
                    "DecalRoot socket location is 0,0,0. Either character is on this coordinate or there is no such socket"))
        }
    }
    else if (!CharacterOwner)
    {
        DecalStartHit = GetOwner()->GetActorLocation();
    }

    DecalEndHit = GetOwner()->GetActorLocation();
    DecalEndHit.Z = GetOwner()->GetActorLocation().Z - DecalTraceDistance;

    bHasDecalHit = GetWorld()->LineTraceSingleByChannel(  //
        DecalHitResult,                                   //
        DecalStartHit,                                    //
        DecalEndHit,                                      //
        ECC_Visibility,
        FCollisionQueryParams(),    //
        FCollisionResponseParams()  //
    );

#if WITH_EDITORONLY_DATA
    if (bIsDecalShadowDebugEnabled)
    {
        DrawDebugLine(
            GetWorld(), DecalStartHit, DecalEndHit, FColor::Emerald, false);
    }
#endif

    SetWorldLocation(DecalHitResult.Location);
}
