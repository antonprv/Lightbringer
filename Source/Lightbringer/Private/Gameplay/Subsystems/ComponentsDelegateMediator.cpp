// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "ComponentsDelegateMediator.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UComponentsDelegateMediator* UComponentsDelegateMediator::Get(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    if (UGameInstance* GI = UGameplayStatics::GetGameInstance(World))
    {
        return GI->GetSubsystem<UComponentsDelegateMediator>();
    }

    return nullptr;
}

void UComponentsDelegateMediator::DispatchPlayerJumpDamage(
    float Velocity, const FHitResult& HitResult)
{
    OnJumpDamage.Broadcast(Velocity, HitResult);
}
