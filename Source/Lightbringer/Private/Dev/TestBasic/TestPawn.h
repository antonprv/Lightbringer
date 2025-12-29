// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

enum class ESimpleInputAxisType : uint8;
class APlayerController;
class UInputActionData;
class UStaticMeshComponent;
class UCameraComponent;

struct FInputActionInstance;

UCLASS()
class LIGHTBRINGER_API ATestPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ATestPawn();

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    float Velocity{250.f};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    UCameraComponent* CameraComponent{nullptr};
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
    UStaticMeshComponent* StaticMeshComponent{nullptr};

    void HandleMovement(const FVector2D& Value);

protected:
    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;

private:
    FVector VelocityVector{FVector::ZeroVector};

    UPROPERTY()
    APlayerController* PlayerController{nullptr};

    bool bIsPossessed{false};
};
