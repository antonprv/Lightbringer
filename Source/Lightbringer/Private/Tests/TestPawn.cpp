// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestPawn.h"
#include "SimpleInputSubsystem.h"
#include "InputManager.h"
#include "InputActionData.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogATestPawn, Log, Log);

// Sets default values
ATestPawn::ATestPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("Root Transform");
    SetRootComponent(SceneComponent);

    InputActionData = LoadObject<UInputActionData>(
        nullptr, TEXT("InputActionData'/Game/Blueprints/Input/"
                      "IAD_TestFly.IAD_TestFly'"));
    if (!IsValid(InputActionData))
    {
        UE_LOG(LogATestPawn, Warning, TEXT("Failed to load InputActionData"));
    }
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

    if (!VelocityVector.IsZero())
    {
        FVector NewPosition =
            GetActorLocation() + Velocity * DeltaTime * VelocityVector;
        SetActorLocation(NewPosition);
    }
}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APlayerController* Controller = GetWorld()->GetFirstPlayerController())
    {
        PlayerController = Controller;
    }

    if (USimpleInputSubsystem* SimpleInputSubsystem =
            USimpleInputSubsystem::Get(GetWorld()))
    {
        if (UInputManager* InputManager =
                SimpleInputSubsystem->GetInputManager())
        {
            InputManager->SetActiveActionData(
                PlayerController, PlayerInputComponent, InputActionData);

            InputManager->OnAxisChanged.AddDynamic(
                this, &ATestPawn::HandleMovement);
        }
    }
}

void ATestPawn::MoveFowrard(float Value)
{
    VelocityVector.X = Value;
    if (Value != 0)
    {
        UE_LOG(LogATestPawn, Display, TEXT("MoveFowrard value: %f"), Value)
    }
}

void ATestPawn::MoveRight(float Value)
{
    VelocityVector.Y = Value;
    if (Value != 0)
    {
        UE_LOG(LogATestPawn, Display, TEXT("MoveRight value: %f"), Value)
    }
}

void ATestPawn::HandleMovement(
    FName AxisName, ESimpleInputAxisType AxisType, float Value)
{
    if (AxisName.IsEqual("MoveForward") && AxisType == ESimpleInputAxisType::X)
    {
        MoveFowrard(Value);
    }
    else if (AxisName.IsEqual("MoveRight") &&
             AxisType == ESimpleInputAxisType::Y)
    {
        MoveRight(Value);
    }
}