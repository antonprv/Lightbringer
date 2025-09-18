// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "LBPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/LBPlayerCharacter.h"

// Sets default values
ALBPlayerCharacter::ALBPlayerCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    SpringArmComponent =
        CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->CameraLagSpeed = 25.f;
    SpringArmComponent->bEnableCameraLag = true;

    CameraComponent =
        CreateDefaultSubobject<UCameraComponent>("Player Camera");
    CameraComponent->SetupAttachment(SpringArmComponent);

    DefaultCameraFOV = CameraComponent->FieldOfView;
    DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called when the game starts or when spawned
void ALBPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ALBPlayerCharacter::Jump()
{
    Super::Jump();
}

// Called every frame
void ALBPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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

void ALBPlayerCharacter::LookUp_Implementation(float& Value)
{
    AddControllerPitchInput(Value);
}

void ALBPlayerCharacter::TurnAround_Implementation(float& Value)
{
    AddControllerYawInput(Value);
}

void ALBPlayerCharacter::JumpUp_Implementation()
{
    Jump();
}

void ALBPlayerCharacter::StartSprinting_Implementation()
{
    bIsSprinting = true;

    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    CameraComponent->FieldOfView = SpwintCameraFOV;
}

void ALBPlayerCharacter::StopSprinting_Implementation()
{
    bIsSprinting = false;
    GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
    CameraComponent->FieldOfView = DefaultCameraFOV;
}
