// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "View/Rendering/GraphicsPresetManager.h"
#include "QualitySettingsSubsystem.generated.h"

/**
 *
 */
UCLASS()
class LIGHTBRINGER_API UQualitySettingsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UQualitySettingsSubsystem* Get(class UWorld* World);

    UFUNCTION(BlueprintPure)
    UGraphicsPresetManager* GetGraphicsPresetManager() const { return Manager; }

protected:
    virtual void Initialize(FSubsystemCollectionBase& Collection);
    virtual void Deinitialize();

private:
    UGraphicsPresetManager* Manager;
};
