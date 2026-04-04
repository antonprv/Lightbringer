// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MathUtilStatics.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EVelocityScaleType : uint8
{
    Meters,
    Kilometers
};

UCLASS()
class MATHUTILS_API UMathUtilStatics : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Math")
    static float CalculateDirection(
        const FVector& Velocity, const FRotator& BaseRotation);

    UFUNCTION(BlueprintCallable, Category = "Math")
    static float CalculateAcceleration(
        const FVector& Velocity, float DeltaTime, EVelocityScaleType VelocityScale);
};
