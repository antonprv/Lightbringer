// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestPlayerController.h"

#include "TestPawn.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

DEFINE_LOG_CATEGORY_STATIC(LogATestPlayerController, Log, Log)

ATestPlayerController::ATestPlayerController() {}

void ATestPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LP = GetLocalPlayer())
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            Subsystem->AddMappingContext(InputMappingContext, 0);

    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(), ATestPawn::StaticClass(), PawnsToPossess);
}

void ATestPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                GetLocalPlayer()))
    {
        if (InputMappingContext)
        {
            Subsystem->RemoveMappingContext(InputMappingContext);
        }
    }

    Super::EndPlay(EndPlayReason);
}

void ATestPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* Input =
            Cast<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(MoveCustom, ETriggerEvent::Triggered, this,
            &ATestPlayerController::HandleMoveCustom);

        Input->BindAction(ChangePawn, ETriggerEvent::Triggered, this,
            &ATestPlayerController::HandleSwitchKey);
    }
}

void ATestPlayerController::HandleMoveCustom(const FInputActionInstance& Input)
{
    if (!InputMappingContext || !GetPawn()) return;

    if (Input.GetValue().GetValueType() == EInputActionValueType::Axis2D)
    {
        if (ATestPawn* TestPawn = Cast<ATestPawn>(GetPawn()))
        {
            TestPawn->HandleMovement(Input.GetValue().Get<FVector2D>());
        }
    }
}

void ATestPlayerController::HandleSwitchKey(const FInputActionInstance& Input)
{
    if (!InputMappingContext || !GetPawn()) return;

    ChangeActivePawn();
}

void ATestPlayerController::ChangeActivePawn()
{
    if (PawnsToPossess.Num() <= 1) return;

    ATestPawn* TestPawn = Cast<ATestPawn>(PawnsToPossess[CurrentPawnIndex]);

    if (!TestPawn) return;

    CurrentPawnIndex = (CurrentPawnIndex + 1) % PawnsToPossess.Num();

    Possess(TestPawn);
    UE_LOG(LogATestPlayerController, Display,
        TEXT("Successfully possessed pawn: %s"), *TestPawn->GetName());
}
