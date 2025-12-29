// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LBPlayerController.generated.h"

class APawn;
class UPlayerDelegateMediator;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

UCLASS()
class LIGHTBRINGER_API ALBPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputMappingContext* InputMappingContext{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* LookAction{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* MoveAction{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* JumpAction{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* SprintAction{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* CrouchAction{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* WalkAction{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* AimAction{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    class UInputAction* PickUpAction{nullptr};

    UFUNCTION(BlueprintCallable)
    inline APawn* GetControlledPawn() { return GetPawn(); };

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
    virtual void SetupInputComponent() override;

private:
    void PawnMove(const FInputActionInstance& Instance);
    void PawnLook(const FInputActionInstance& Instance);
    void PawnJump(const FInputActionInstance& Instance);
    void PawnSprint(const FInputActionInstance& Instance);
    void PawnCrouch(const FInputActionInstance& Instance);
    void PawnWalk(const FInputActionInstance& Instance);
    void PawnAim(const FInputActionInstance& Instance);
    void PawnPickUp(const FInputActionInstance& Instance);

    UPROPERTY()
    UPlayerDelegateMediator* DelegateMediator{nullptr};

    void OnPawnDeath(APawn* PlayerPawn);
    void OnPawnDestruction(AActor* DestroyedPawnActor);
};
