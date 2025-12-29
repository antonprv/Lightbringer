// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "TestPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogATestPawn, Log, Log);

// Sets default values
ATestPawn::ATestPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    // Components
    StaticMeshComponent =
        CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
    SetRootComponent(StaticMeshComponent);
    StaticMeshComponent->SetGenerateOverlapEvents(true);
    StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
    StaticMeshComponent->SetConstraintMode(EDOFMode::XYPlane);
    StaticMeshComponent->SetLinearDamping(10.f);
    StaticMeshComponent->SetAngularDamping(10.f);
    StaticMeshComponent->SetCastShadow(false);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(GetRootComponent());
}

void ATestPawn::HandleMovement(const FVector2D& Value)
{
    VelocityVector = {Value.Y, Value.X, 0.f};
    VelocityVector.Normalize();
    AddActorLocalOffset(
        VelocityVector * Velocity * GetWorld()->GetDeltaSeconds(),
        true);
    if (Value.IsZero())
    {
        UE_LOG(LogATestPawn, Display, TEXT("MoveForward value: X=%f, Y=%f"),
            Value.X, Value.Y);
    }
}

void ATestPawn::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    UE_LOG(LogATestPawn, Display, TEXT("%s possessed by %s"), *GetName(),
        *NewController->GetName())
    bIsPossessed = true;
}

void ATestPawn::UnPossessed()
{
    Super::UnPossessed();

    UE_LOG(LogATestPawn, Display, TEXT("%s unpossessed"), *GetName())
    bIsPossessed = false;
}
