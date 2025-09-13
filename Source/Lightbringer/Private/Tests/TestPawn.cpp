// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestPawn.h"
#include "SimpleInputSubsystem.h"
#include "InputManager.h"
#include "InputActionData.h"

// Sets default values
ATestPawn::ATestPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (USimpleInputSubsystem* SimpleInputSubsystem =
            USimpleInputSubsystem::Get(GetWorld()))
    {
        if (UInputManager* InputManager =
                SimpleInputSubsystem->GetInputManager())
        {
            InputManager->SetActiveActionData(
                PlayerInputComponent, InputActionData);

            InputManager->OnAxisChanged.AddDynamic(
                this, &ATestPawn::HandleMovement);
        }
    }
}

void ATestPawn::MoveFowrard(float Value) {}

void ATestPawn::MoveRight(float Value) {}

void ATestPawn::HandleMovement(
    FName AxisName, ESimpleInputAxisType AxisType, float Value)
{
    if (AxisName.IsEqual("") && AxisType == ESimpleInputAxisType::Y)
    {
        // do stuff with value
    }
    else if (AxisName.IsEqual("") && AxisType == ESimpleInputAxisType::X)
    {
        // do stuff with value
    }
}
