// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

enum class ESimpleInputAxisType : uint8;
class APlayerController;
class UInputActionData;
class UStaticMeshComponent;
class UCameraComponent;

class UInputComponent;
class UInputManager;

UCLASS()
class ATestPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ATestPawn();

    UPROPERTY(VisibleAnywhere, Category = "Input")
    float Velocity{50.f};

    UPROPERTY(VisibleAnywhere, Category = "Input")
    UInputActionData* InputActionData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    UCameraComponent* CameraComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    UStaticMeshComponent* StaticMeshComponent{nullptr};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;

public:
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

private:
    FVector VelocityVector{FVector::ZeroVector};

    UPROPERTY()
    UInputManager* InputManager{nullptr};

    UPROPERTY()
    APlayerController* PlayerController{nullptr};

    void MoveFowrard(float Value);
    void MoveRight(float Value);
    UFUNCTION()
    void HandleMovement(
        FName AxisName, ESimpleInputAxisType AxisType, float Value);

    bool bIsPossessed{false};
};
