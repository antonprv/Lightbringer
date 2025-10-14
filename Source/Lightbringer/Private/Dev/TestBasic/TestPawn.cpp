// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Controller.h"

#include "SimpleInputSubsystem.h"
#include "InputManager.h"
#include "InputActionData.h"

DEFINE_LOG_CATEGORY_STATIC(LogATestPawn, Log, Log);

// Sets default values
ATestPawn::ATestPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_DuringPhysics;

    // Components
    StaticMeshComponent =
        CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
    SetRootComponent(StaticMeshComponent);
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(GetRootComponent());

    // Input
    InputActionData = LoadObject<UInputActionData>(
        nullptr, TEXT("InputActionData'/Game/Blueprints/Test/Input/"
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

    StaticMeshComponent->SetConstraintMode(EDOFMode::XYPlane);
    StaticMeshComponent->SetLinearDamping(1.f);
    StaticMeshComponent->SetAngularDamping(1.f);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerController = GetWorld()->GetFirstPlayerController();

    if (USimpleInputSubsystem* SimpleInputSubsystem =
            USimpleInputSubsystem::Get(GetWorld()))
    {
        InputManager = SimpleInputSubsystem->GetInputManager();

        if (InputManager)
        {
            InputManager->SetActiveActionData(
                PlayerController, PlayerInputComponent, InputActionData);

            if (!InputManager->OnAxisChanged.GetAllObjects().Contains(this))
            {
                InputManager->OnAxisChanged.AddDynamic(
                    this, &ATestPawn::HandleMovement);
            }
        }
    }
}

void ATestPawn::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    UE_LOG(LogATestPawn, Display, TEXT("%s possessed by %s"), *GetName(),
        *NewController->GetName())
    bIsPossessed = true;
}

void ATestPawn::UnPossessed()
{
    Super::UnPossessed();

    UE_LOG(LogATestPawn, Display, TEXT("%s unpossessed"), *GetName())
    bIsPossessed = false;
}

void ATestPawn::MoveFowrard(float Value)
{
    if (!bIsPossessed) return;

    VelocityVector.X = Value;

    AddActorLocalOffset(
        VelocityVector * Velocity * GetWorld()->GetDeltaSeconds(), true);

    if (Value != 0)
    {
        UE_LOG(LogATestPawn, Display, TEXT("MoveFowrard value: %f"), Value)
    }
}

void ATestPawn::MoveRight(float Value)
{
    if (!bIsPossessed) return;

    VelocityVector.Y = Value;

    AddActorLocalOffset(
        VelocityVector * Velocity * GetWorld()->GetDeltaSeconds(), true);

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
