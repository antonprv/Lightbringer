// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InputManager.h"
#include "SimpleInputSubsystem.generated.h"

/**
 *
 */
UCLASS()
class SIMPLEINPUT_API USimpleInputSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static USimpleInputSubsystem* Get(class UWorld* World);

    UFUNCTION(BlueprintPure)
    UInputManager* GetInputManager() const { return InputManager; }

protected:
    virtual void Initialize(FSubsystemCollectionBase& Collection);
    virtual void Deinitialize();

private:
    UInputManager* InputManager;
};
