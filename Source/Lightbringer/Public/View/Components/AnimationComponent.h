// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationComponent.generated.h"

class UAnimMontage;
class ACharacter;
class UComponentsDelegateMediator;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIGHTBRINGER_API UAnimationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAnimationComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* DeathMontage{nullptr};

private:
    UPROPERTY()
    UComponentsDelegateMediator* ComponentsDelegateMediator{nullptr};
    UPROPERTY()
    ACharacter* CharacterOwner{nullptr};

    void PlayDeathAnimation(AActor* DeadActor);
};
