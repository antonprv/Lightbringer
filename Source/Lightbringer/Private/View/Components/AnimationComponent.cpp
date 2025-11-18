// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Components/AnimationComponent.h"

#include "Gameplay/Subsystems/ComponentsDelegateMediator.h"
#include "Animation/AnimMontage.h"

#include "Engine/World.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogUAnimationComponent, Log, Log)

// Sets default values for this component's properties
UAnimationComponent::UAnimationComponent()
{
    // Set this component to be initialized when the game starts, and to be
    // ticked every frame.  You can turn these features off to improve
    // performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UAnimationComponent::BeginPlay()
{
    Super::BeginPlay();
    CharacterOwner = Cast<ACharacter>(GetOwner());
    ComponentsDelegateMediator = UComponentsDelegateMediator::Get(GetWorld());

    check(CharacterOwner);
    check(ComponentsDelegateMediator);

    if (!ComponentsDelegateMediator->OnActorDeath.IsBoundToObject(this))
    {
        ComponentsDelegateMediator->OnActorDeath.AddUObject(
            this, &UAnimationComponent::PlayDeathAnimation);
    }
}
void UAnimationComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    if (ComponentsDelegateMediator->OnActorDeath.IsBoundToObject(this))
    {
        ComponentsDelegateMediator->OnActorDeath.RemoveAll(this);
    }

    Super::EndPlay(EndPlayReason);
}

void UAnimationComponent::PlayDeathAnimation(AActor* DeadActor)
{
    if (!CharacterOwner || !DeathMontage)
    {
        UE_LOG(LogUAnimationComponent, Error,
            TEXT("CharacterOwner or DeathMontage is null!"))
        return;
    }

    if (GetOwner() == DeadActor)
    {
        CharacterOwner->PlayAnimMontage(DeathMontage);
    }
}
