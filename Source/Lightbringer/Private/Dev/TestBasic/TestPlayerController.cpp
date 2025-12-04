// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Dev/TestBasic/TestPlayerController.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "SimpleInputSubsystem.h"
#include "InputManager.h"
#include "InputActionData.h"

#include "Dev/TestBasic/TestPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogATestPlayerController, Log, Log)

ATestPlayerController::ATestPlayerController()
{
    // Input
    InputData = LoadObject<UInputActionData>(
        nullptr, TEXT("InputActionData'/Game/Blueprints/Test/Input/"
                      "IAD_TestFly.IAD_TestFly'"));
    if (!IsValid(InputData))
    {
        UE_LOG(LogATestPlayerController, Warning,
            TEXT("Failed to load InputActionData"));
    }

    CurrentPawnIndex = 0;
}

void ATestPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld())
    {
        UE_LOG(LogATestPlayerController, Error,
            TEXT("GetWorld() is nullptr in BeginPlay!"));
        return;
    }

    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(), ATestPawn::StaticClass(), PawnsToPossess);

    ValidatePawns();
}

void ATestPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (InputManager)
    {
        InputManager->OnActionPressed.RemoveDynamic(
            this, &ATestPlayerController::HandleSwitchKey);
    }

    Super::EndPlay(EndPlayReason);
}

void ATestPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (USimpleInputSubsystem* SimpleInputSubsystem =
            USimpleInputSubsystem::Get(GetWorld()))
    {
        InputManager = SimpleInputSubsystem->GetInputManager();
        if (InputManager)
        {
            InputManager->SetActiveActionData(this, InputComponent, InputData);

            InputManager->OnActionPressed.AddDynamic(
                this, &ATestPlayerController::HandleSwitchKey);
        }
    }
}

void ATestPlayerController::HandleSwitchKey(FName ActionName)
{
    if (ActionName.IsEqual("SwitchPawn"))
    {
        SwitchPawn();
    }
}

void ATestPlayerController::SwitchPawn()
{
    if (PawnsToPossess.Num() <= 1) return;

    ATestPawn* TestPawn = Cast<ATestPawn>(PawnsToPossess[CurrentPawnIndex]);

    if (!TestPawn) return;

    CurrentPawnIndex = (CurrentPawnIndex + 1) % PawnsToPossess.Num();

    Possess(TestPawn);
    UE_LOG(LogATestPlayerController, Display,
        TEXT("Successfully possessed pawn: %s"), *TestPawn->GetName());
}

void ATestPlayerController::ValidatePawns()
{
    TArray<AActor*> ValidPawns;
    for (AActor* PawnToPossess : PawnsToPossess)
    {
        if (PawnToPossess && IsValid(PawnToPossess) &&
            PawnToPossess->IsA<ATestPawn>())
        {
            ValidPawns.Add(PawnToPossess);
        }
    }
    PawnsToPossess = ValidPawns;

    if (PawnsToPossess.Num() <= 1)
    {
        UE_LOG(LogATestPlayerController, Warning,
            TEXT("Not enough valid pawns to possess"));
        return;
    }
}
