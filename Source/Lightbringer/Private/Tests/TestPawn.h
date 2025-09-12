// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

enum class ESimpleInputAxisType : uint8;

UCLASS()
class ATestPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ATestPawn();

    UPROPERTY(EditAnywhere)
    float Velocity{300.f};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

private:
    void MoveFowrard(float Amount);
    void MoveRight(float Amount);
    void HandleMovement(
        FName AxisName, ESimpleInputAxisType AxisType, float Value);
};
