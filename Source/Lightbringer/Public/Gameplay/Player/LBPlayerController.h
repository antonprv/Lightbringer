// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionData.h"
#include "LBPlayerController.generated.h"

/**
 *
 */
UCLASS()
class LIGHTBRINGER_API ALBPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ALBPlayerController();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    UInputActionData* InputActionData{nullptr};

protected:
    virtual void SetupInputComponent() override;

private:
    UFUNCTION()
    void ProcessInput(
        FName ActionName, ESimpleInputAxisType AxisType, float Value);
    void MovePawnForward(float Value);
    void MovePawnRight(float Value);
};
