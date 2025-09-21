// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Gameplay/Subsystems/DelegateMediatorSubsystem.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UDelegateMediatorSubsystem* UDelegateMediatorSubsystem::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<UDelegateMediatorSubsystem>();
    }

    return nullptr;
}

void UDelegateMediatorSubsystem::DispatchPlayerDeath(APawn* DeadPawn)
{
    OnPlayerDeath.Broadcast(DeadPawn);
}

void UDelegateMediatorSubsystem::DispatchPlayerJumpDamage(
    float Velocity, const FHitResult& HitResult)
{
    OnJumpDamage.Broadcast(Velocity, HitResult);
}
