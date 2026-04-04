// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

UCLASS()
class LIGHTBRINGER_API ATestPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    ATestPlayerController();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* InputMappingContext{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveCustom{nullptr};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* ChangePawn{nullptr};

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void SetupInputComponent() override;

private:
    TArray<AActor*> PawnsToPossess{};
    int32 CurrentPawnIndex{0};

    void HandleMoveCustom(const FInputActionInstance& Input);
    void HandleSwitchKey(const FInputActionInstance& Input);

    void ChangeActivePawn();
};
