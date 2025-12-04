// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "LBGameInstance.generated.h"

UCLASS()
class LIGHTBRINGER_API ULBGameInstance : public UGameInstance
{
    GENERATED_BODY()

protected:
    virtual void OnStart() override;
    virtual void Shutdown() override;

private:
    void ApplyGraphicsSettingsAfterWorld(
        UWorld* World, const UWorld::InitializationValues IVS);    
};