// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "View/Player/Animation/LBPlayerAnimationComponent.h"

#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "View/Player/LBPlayerCharacter.h"
#include "Gameplay/Components/LBCharacterMovementComponent.h"

void ULBPlayerAnimationComponent::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = Cast<ALBPlayerCharacter>(GetOwner());
    check(PlayerCharacter);
}

FRotator ULBPlayerAnimationComponent::GetLookDirection()
{
    PlayerCharacter = Cast<ALBPlayerCharacter>(GetOwner());
    check(PlayerCharacter);

    return UKismetMathLibrary::NormalizedDeltaRotator(
        PlayerCharacter->GetBaseAimRotation(),
        PlayerCharacter->GetActorRotation());
}

float ULBPlayerAnimationComponent::GetVelocity()
{
    PlayerCharacter = Cast<ALBPlayerCharacter>(GetOwner());
    check(PlayerCharacter);

    return PlayerCharacter->GetVelocity().Size2D();
}

float ULBPlayerAnimationComponent::GetDirection()
{
    PlayerCharacter = Cast<ALBPlayerCharacter>(GetOwner());
    check(PlayerCharacter);

    return UKismetAnimationLibrary::CalculateDirection(
        PlayerCharacter->GetVelocity(), PlayerCharacter->GetActorRotation());
}
