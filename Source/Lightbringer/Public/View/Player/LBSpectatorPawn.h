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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Speed{0.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float SprintSpeed{0.f};

    virtual void MoveCustom_Implementation(const FVector2D Value) override;
    virtual void LookCustom_Implementation(const FVector2D Value) override;
    virtual void JumpCustom_Implementation() override;
    virtual void SprintToggleCustom_Implementation() override;
    virtual void SprintCustom_Implementation(
        const bool bWantsToSprint) override;
    virtual void CrouchCustom_Implementation(
        const bool bWantsToCrouch) override;
    virtual void WalkCustom_Implementation(const bool bWantsToWalk) override;
    virtual void WalkToggleCustom_Implementation() override;
    virtual void AimCustom_Implementation(const bool bWantsToAim) override;
    virtual void PickCustom_Implementation() override;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
    bool bSprintToggle{false};

    UFUNCTION()
    void HandleDestruction(AActor* DestroyedActor);

    void ToggleSprint(const bool bCanSprint);
};
