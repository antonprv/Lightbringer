// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerControllable.h"
#include "LBPlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class LIGHTBRINGER_API ALBPlayerCharacter : public ACharacter,
                                            public IPlayerControllable
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ALBPlayerCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent{nullptr};

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;  // Tick disabled for now

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    void MoveForward_Implementation(float& Value) override;
    void MoveRight_Implementation(float& Value) override;
};
