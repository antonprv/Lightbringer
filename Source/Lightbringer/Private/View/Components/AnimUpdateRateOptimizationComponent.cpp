// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Components/AnimUpdateRateOptimizationComponent.h"
#include "SkeletalMeshComponentBudgeted.h"

DEFINE_LOG_CATEGORY_STATIC(LogALBCharacterBase, Log, Log)

// Helper macro for safe logging
#define CHECK_MESH_AND_PARAMS(FuncName)                                   \
    if (!CharacterMesh)                                                   \
    {                                                                     \
        UE_LOG(LogALBCharacterBase, Error,                                \
            TEXT("%s - SkinnedMeshComponentBudgeted is null."),           \
            TEXT(#FuncName));                                             \
        return;                                                           \
    }                                                                     \
    if (!CharacterMesh->AnimUpdateRateParams)                             \
    {                                                                     \
        UE_LOG(LogALBCharacterBase, Error,                                \
            TEXT("%s - AnimUpdateRateParams is null."), TEXT(#FuncName)); \
        return;                                                           \
    }

// Sets default values
UAnimUpdateRateOptimizationComponent::UAnimUpdateRateOptimizationComponent(
    const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    // Set this character to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryComponentTick.bCanEverTick = false;

    InitializeDefaultValues();
    SetupAnimUpdateParams();
}

void UAnimUpdateRateOptimizationComponent::InitializeDefaultValues()
{
    AnimUpdateRate = 60;
    OffScreenFramesSkip = 80;
    bInterpolateSkippedFrames = true;

    DistanceFactorThesholds = {
        0.50f,  // Near: fully update (0 skip)
        0.25f,  // Mid: skip 1 frame
        0.12f,  // Far: skip 2 frames
        0.06f,  // Very far: skip 3 frames
        0.03f   // Extreme far: skip 4–5 frames
    };

    LODSkipMap.Add(0, 0);   // Full quality for LOD0
    LODSkipMap.Add(1, 1);   // LOD1: skip 1 frame (~30 FPS update)
    LODSkipMap.Add(2, 3);   // LOD2: skip 3 frames (~15 FPS update)
    LODSkipMap.Add(3, 7);   // LOD3: skip 7 frames (~7 FPS update)
    LODSkipMap.Add(4, 15);  // LOD4: skip 15 frames (~4 FPS update)
}

// Called when the game starts or when spawned
void UAnimUpdateRateOptimizationComponent::BeginPlay()
{
    Super::BeginPlay();

    CharacterOwner = Cast<ACharacter>(GetOwner());
    check(CharacterOwner);

    CharacterMesh =
        Cast<USkeletalMeshComponentBudgeted>(CharacterOwner->GetMesh());
    check(CharacterMesh);

    CharacterMesh->bEnableUpdateRateOptimizations = true;

    if (CharacterMesh->OnAnimInitialized.Contains(this,
            GET_FUNCTION_NAME_CHECKED(UAnimUpdateRateOptimizationComponent,
                InitializeAnimUpdateRateParams)))
    {
        CharacterMesh->OnAnimInitialized.AddDynamic(
            this, &UAnimUpdateRateOptimizationComponent::
                      InitializeAnimUpdateRateParams);
    }
}

void UAnimUpdateRateOptimizationComponent::EndPlay(
    EEndPlayReason::Type EndPlayReason)
{
    if (CharacterMesh)
    {
        if (CharacterMesh->OnAnimInitialized.Contains(this,
                GET_FUNCTION_NAME_CHECKED(UAnimUpdateRateOptimizationComponent,
                    InitializeAnimUpdateRateParams)))
        {
            CharacterMesh->OnAnimInitialized.RemoveDynamic(
                this, &UAnimUpdateRateOptimizationComponent::
                          InitializeAnimUpdateRateParams);
        }

        if (CharacterMesh->AnimUpdateRateParams == &AnimUpdateParams)
        {
            CharacterMesh->AnimUpdateRateParams = nullptr;
        }
    }

    Super::EndPlay(EndPlayReason);
}

void UAnimUpdateRateOptimizationComponent::InitializeAnimUpdateRateParams()
{
    CHECK_MESH_AND_PARAMS(GET_FUNCTION_NAME_CHECKED(
        UAnimUpdateRateOptimizationComponent, InitializeAnimUpdateRateParams))

    CharacterMesh->AnimUpdateRateParams = &AnimUpdateParams;
}

void UAnimUpdateRateOptimizationComponent::SetupAnimUpdateParams()
{
    AnimUpdateParams.BaseVisibleDistanceFactorThesholds.Reset();

    AnimUpdateParams.BaseVisibleDistanceFactorThesholds =
        DistanceFactorThesholds;

    AnimUpdateParams.LODToFrameSkipMap = LODSkipMap;

    AnimUpdateParams.MaxEvalRateForInterpolation = AnimUpdateRate;

    AnimUpdateParams.BaseNonRenderedUpdateRate = OffScreenFramesSkip;

    AnimUpdateParams.bInterpolateSkippedFrames = bInterpolateSkippedFrames;
}

void UAnimUpdateRateOptimizationComponent::SetUpdateRateOptimisationMode(
    EAnimOptimisationMode UpdateRateOptimisationMode)
{
    CHECK_MESH_AND_PARAMS(GET_FUNCTION_NAME_CHECKED(
        UAnimUpdateRateOptimizationComponent, SetUpdateRateOptimisationMode))

    switch (UpdateRateOptimisationMode)
    {
        case EAnimOptimisationMode::VisibleDistanceFactorThresholds:
            CharacterMesh->AnimUpdateRateParams->bShouldUseLodMap = false;
            break;
        case EAnimOptimisationMode::LODSkipMap:
            CharacterMesh->AnimUpdateRateParams->bShouldUseLodMap = true;
            break;
        default:
            break;
    }
}

void UAnimUpdateRateOptimizationComponent::SetVisibleDistanceFactorThresholds(
    const TArray<float>& VisibleDistanceFactorThesholds)
{
    CHECK_MESH_AND_PARAMS(
        GET_FUNCTION_NAME_CHECKED(UAnimUpdateRateOptimizationComponent,
            SetVisibleDistanceFactorThresholds))

    AnimUpdateParams.BaseVisibleDistanceFactorThesholds.Reset();

    for (float MaxDistanceThreshold : VisibleDistanceFactorThesholds)
    {
        AnimUpdateParams.BaseVisibleDistanceFactorThesholds.Add(
            MaxDistanceThreshold);
    }
}

TArray<float> UAnimUpdateRateOptimizationComponent::
    GetVisibleDistanceFactorThresholds()
{
    if (!CharacterMesh || !CharacterMesh->AnimUpdateRateParams)
    {
        return TArray<float>();
    }

    return CharacterMesh->AnimUpdateRateParams
        ->BaseVisibleDistanceFactorThesholds;
}

void UAnimUpdateRateOptimizationComponent::SetLODToFrameSkipMap(
    const TMap<int32, int32>& LODFrameSkipMap)
{
    CHECK_MESH_AND_PARAMS(GET_FUNCTION_NAME_CHECKED(
        UAnimUpdateRateOptimizationComponent, SetLODToFrameSkipMap))

    AnimUpdateParams.LODToFrameSkipMap = LODFrameSkipMap;
}

TMap<int32, int32> UAnimUpdateRateOptimizationComponent::GetLODToFrameSkipMap()
{
    if (!CharacterMesh || !CharacterMesh->AnimUpdateRateParams)
    {
        return TMap<int32, int32>();
    }

    return CharacterMesh->AnimUpdateRateParams->LODToFrameSkipMap;
}

bool UAnimUpdateRateOptimizationComponent::IsOptimized()
{
    if (!CharacterMesh)
    {
        return false;
    }

    return CharacterMesh->bEnableUpdateRateOptimizations;
}

void UAnimUpdateRateOptimizationComponent::SetMaxEvalRateForInterpolation(
    int UpdateRate)
{
    CHECK_MESH_AND_PARAMS(GET_FUNCTION_NAME_CHECKED(
        UAnimUpdateRateOptimizationComponent, SetMaxEvalRateForInterpolation))

    AnimUpdateParams.MaxEvalRateForInterpolation = UpdateRate;
}

int32 UAnimUpdateRateOptimizationComponent::GetMaxEvalRateForInterpolation()
{
    if (!CharacterMesh)
    {
        UE_LOG(LogALBCharacterBase, Error,
            TEXT(
                "GetMaxEvalRateForInterpolation - SkinnedMeshComponent is null."));
        return 0;
    }
    if (!CharacterMesh->AnimUpdateRateParams)
    {
        UE_LOG(LogALBCharacterBase, Error,
            TEXT(
                "GetMaxEvalRateForInterpolation - AnimUpdateRateParams is null."));
        return 0;
    }

    return CharacterMesh->AnimUpdateRateParams->MaxEvalRateForInterpolation;
}

void UAnimUpdateRateOptimizationComponent::SetBaseNonRenderedUpdateRate(
    int OffScreenFramesToSkip)
{
    CHECK_MESH_AND_PARAMS(GET_FUNCTION_NAME_CHECKED(
        UAnimUpdateRateOptimizationComponent, SetBaseNonRenderedUpdateRate))

    AnimUpdateParams.BaseNonRenderedUpdateRate = OffScreenFramesToSkip;
}

int32 UAnimUpdateRateOptimizationComponent::GetBaseNonRenderedUpdateRate()
{
    if (!CharacterMesh)
    {
        UE_LOG(LogALBCharacterBase, Error,
            TEXT(
                "GetMaxEvalRateForInterpolation - SkinnedMeshComponent is null."));
        return 0;
    }
    if (!CharacterMesh->AnimUpdateRateParams)
    {
        UE_LOG(LogALBCharacterBase, Error,
            TEXT(
                "GetMaxEvalRateForInterpolation - AnimUpdateRateParams is null."));
        return 0;
    }

    return CharacterMesh->AnimUpdateRateParams->BaseNonRenderedUpdateRate;
}

void UAnimUpdateRateOptimizationComponent::SetInterpolateSkippedFrames(
    bool bEnable)
{
    CHECK_MESH_AND_PARAMS(GET_FUNCTION_NAME_CHECKED(
        UAnimUpdateRateOptimizationComponent, SetInterpolateSkippedFrames))

    AnimUpdateParams.bInterpolateSkippedFrames = bEnable;
}

bool UAnimUpdateRateOptimizationComponent::GetInterpolateSkippedFrames()
{
    if (!CharacterMesh) return false;
    if (!CharacterMesh->AnimUpdateRateParams)
    {
        UE_LOG(LogALBCharacterBase, Error,
            TEXT(
                "GetInterpolateSkippedFrames - AnimUpdateRateParams is null."));
        return false;
    }

    return CharacterMesh->AnimUpdateRateParams->bInterpolateSkippedFrames;
}
