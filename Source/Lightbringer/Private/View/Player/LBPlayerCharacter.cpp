// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "..\..\..\Public\View\Player\LBPlayerCharacter.h"

// Sets default values
ALBPlayerCharacter::ALBPlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    CameraComponent =
        CreateDefaultSubobject<UCameraComponent>("Player Camera");
    CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ALBPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ALBPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tick disabled for now
}

// Called to bind functionality to input
void ALBPlayerCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALBPlayerCharacter::MoveForward_Implementation(float& Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void ALBPlayerCharacter::MoveRight_Implementation(float& Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}