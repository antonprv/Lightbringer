// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "LightbringerGameInstance.generated.h"

/**
 *
 */
UCLASS()
class LIGHTBRINGER_API ULightbringerGameInstance : public UGameInstance
{
    GENERATED_BODY()

protected:
    virtual void OnStart();
    virtual void Shutdown();

private:
    void ApplyGraphicsSettingsAfterWorld(UWorld* World, const UWorld::InitializationValues IVS);
};
