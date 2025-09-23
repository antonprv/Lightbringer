// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "PlayerDelegateMediator.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UPlayerDelegateMediator* UPlayerDelegateMediator::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<UPlayerDelegateMediator>();
    }

    return nullptr;
}

void UPlayerDelegateMediator::DispatchPlayerDestruction(AActor* PlayerActor)
{
    OnPlayerDestruction.Broadcast(PlayerActor);
}

void UPlayerDelegateMediator::DispatchPlayerDeath(APawn* DeadPawn)
{
    OnPlayerDeath.Broadcast(DeadPawn);
}
