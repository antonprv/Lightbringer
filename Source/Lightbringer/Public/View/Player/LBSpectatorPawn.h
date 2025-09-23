// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "Interfaces/PlayerControllable.h"
#include "LBSpectatorPawn.generated.h"

/**
 *
 */
UCLASS()
class LIGHTBRINGER_API ALBSpectatorPawn : public ASpectatorPawn,
                                          public IPlayerControllable
{
    GENERATED_BODY()

public:
    ALBSpectatorPawn();

    virtual void MoveForwardCustom_Implementation(const float& Value) override;
    virtual void MoveRightCustom_Implementation(const float& Value) override;
    virtual void LookUpCustom_Implementation(const float& Value) override;
    virtual void TurnAroundCustom_Implementation(const float& Value) override;
    virtual void JumpCustom_Implementation() override;
    virtual void StartSprinting_Implementation() override;
    virtual void StopSprinting_Implementation() override;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
    UFUNCTION()
    void HandleDestruction(AActor* DestroyedActor);
};
