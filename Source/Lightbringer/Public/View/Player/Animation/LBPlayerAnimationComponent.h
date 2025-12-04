// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "View/Components/AnimationComponent.h"
#include "LBPlayerAnimationComponent.generated.h"

/**
 *
 */

class ALBPlayerCharacter;
class UAnimationSharingSetup;
class UAnimationSharingManager;
class ULBCharacterMovementComponent;

UCLASS()
class ULBPlayerAnimationComponent : public UAnimationComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FRotator GetLookDirection();

    UFUNCTION(BlueprintCallable)
    float GetVelocity();
    UFUNCTION(BlueprintCallable)
    float GetDirection();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ALBPlayerCharacter* PlayerCharacter{nullptr};

    // Upper body movement
    FRotator DeltaRotator;
};
