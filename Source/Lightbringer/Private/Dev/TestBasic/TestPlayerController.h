// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

class UInputActionData;
class UInputManager;

UCLASS()
class ATestPlayerController : public APlayerController
{
    GENERATED_BODY()

    ATestPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void SetupInputComponent() override;

private:
    TArray<AActor*> PawnsToPossess{};
    TArray<AActor*> ValidPawnsToPossess{};
    
    int32 CurrentPawnIndex{0};

    UPROPERTY()
    UInputActionData* InputData{nullptr};
    UPROPERTY()
    UInputManager* InputManager{nullptr};

    UFUNCTION()
    void HandleSwitchKey(FName ActionName);
    void SwitchPawn();
    void ValidatePawns();
};
