// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionData.h"
#include "LBPlayerController.generated.h"

class APawn;
class UPlayerDelegateMediator;

UCLASS()
class LIGHTBRINGER_API ALBPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ALBPlayerController();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UInputActionData* InputActionData{nullptr};

    UFUNCTION(BlueprintCallable)
    inline APawn* GetControlledPawn() { return GetPawn(); };

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
    virtual void SetupInputComponent() override;

private:
    UFUNCTION()
    void ProcessInput(
        FName ActionName, ESimpleInputAxisType AxisType, float Value);
    UFUNCTION()
    void ProcessPressed(FName ActionName);
    UFUNCTION()
    void ProcessHold(FName ActionName);
    UFUNCTION()
    void ProcessReleased(FName ActionName);

    void MovePawnForward(float Value);
    void MovePawnRight(float Value);
    void PawnLookUp(float Value);
    void PawnTurnAround(float Value);
    void PawnJump();
    void PawnStartSprinting();
    void PawnStopSprinting();

    UPROPERTY()
    UPlayerDelegateMediator* DelegateMediator{nullptr};

    void OnPawnDeath(APawn* PlayerPawn);
    void OnPawnDestruction(AActor* DestroyedPawnActor);
};
