// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "ECStateSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"

UECStateSubsystem* UECStateSubsystem::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<UECStateSubsystem>();
    }

    return nullptr;
}

void UECStateSubsystem::BeginSpectating(
    AController* Controller, TSubclassOf<ASpectatorPawn> SpectatorPawnClass)
{
    if (!Controller || IsSpectating()) return;

    FVector ViewLocation;
    FRotator ViewRotation;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    CustomSpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(
        SpectatorPawnClass, ViewLocation, ViewRotation);
    Controller->UnPossess();
    Controller->Possess(CustomSpectatorPawn);

    CurrentState = ESpectatingState::Spectating;
}

void UECStateSubsystem::RespawnInWorld(
    AGameModeBase* GameMode, AController* Controller)
{
    if (!Controller || !GameMode || IsPlaying()) return;

    if (CustomSpectatorPawn)
    {
        Controller->UnPossess();
        CustomSpectatorPawn->Destroy();
        CustomSpectatorPawn = nullptr;
    }

    if (GameMode)
    {
        GameMode->RestartPlayer(Controller);
    }

    CurrentState = ESpectatingState::Playing;
}
