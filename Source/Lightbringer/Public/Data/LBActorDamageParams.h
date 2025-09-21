// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LBActorDamageParams.generated.h"

/**
 *
 */
UCLASS()
class LIGHTBRINGER_API ULBActorDamageParams : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landing",
        meta = (Tooltip =
                    "Lower and upper velocity bounds. Fall damage is mapped to these values"))
    FVector2D FallVelocityBounds{900.f, 1200.f};
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Landing",
        meta =
            (Tooltip = "These damage values are mapped onto velocity bounds"))
    FVector2D FallVelocityDamage{10.f, 100.f};
};
