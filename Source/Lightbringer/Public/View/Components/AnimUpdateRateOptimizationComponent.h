// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimUpdateRateOptimizationComponent.generated.h"

UENUM()
enum class EAnimOptimisationMode : uint8
{
    None,
    VisibleDistanceFactorThresholds,
    LODSkipMap
};

class USkeletalMeshComponentBudgeted;

UCLASS()
class LIGHTBRINGER_API UAnimUpdateRateOptimizationComponent
    : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    UAnimUpdateRateOptimizationComponent(const FObjectInitializer& ObjInit);

    UFUNCTION(BlueprintCallable)
    void SetUpdateRateOptimisationMode(
        EAnimOptimisationMode UpdateRateOptimisationMode);

    UFUNCTION(BlueprintCallable)
    void SetVisibleDistanceFactorThresholds(
        const TArray<float>& VisibleDistanceFactorThesholds);
    UFUNCTION(BlueprintCallable)
    TArray<float> GetVisibleDistanceFactorThresholds();

    UFUNCTION(BlueprintCallable)
    void SetLODToFrameSkipMap(const TMap<int32, int32>& LODFrameSkipMap);
    UFUNCTION(BlueprintCallable)
    TMap<int32, int32> GetLODToFrameSkipMap();

    UFUNCTION(BlueprintCallable)
    void SetMaxEvalRateForInterpolation(int UpdateRate);
    UFUNCTION(BlueprintCallable)
    int32 GetMaxEvalRateForInterpolation();

    UFUNCTION(BlueprintCallable)
    void SetBaseNonRenderedUpdateRate(int OffScreenFramesToSkip);
    UFUNCTION(BlueprintCallable)
    int32 GetBaseNonRenderedUpdateRate();

    UFUNCTION(BlueprintCallable)
    void SetInterpolateSkippedFrames(bool bEnable);
    UFUNCTION(BlueprintCallable)
    bool GetInterpolateSkippedFrames();

    bool IsOptimized();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

    void InitializeAnimUpdateRateParams();

private:
    UPROPERTY()
    ACharacter* CharacterOwner{nullptr};
    UPROPERTY()
    USkeletalMeshComponentBudgeted* CharacterMesh{nullptr};

    FAnimUpdateRateParameters AnimUpdateParams;
    TArray<float> DistanceFactorThesholds{};
    TMap<int32, int32> LODSkipMap{};
    int AnimUpdateRate{60};
    int OffScreenFramesSkip{80};
    bool bInterpolateSkippedFrames{false};

    // Set aggressive optimization params
    void InitializeDefaultValues();
    // Assign aggressive optimization params
    void SetupAnimUpdateParams();
};
