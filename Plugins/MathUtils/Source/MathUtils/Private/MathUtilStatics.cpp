// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "MathUtilStatics.h"

float UMathUtilStatics::CalculateDirection(
    const FVector& Velocity, const FRotator& BaseRotation)
{
    if (!Velocity.IsNearlyZero())
    {
        FMatrix RotMatrix = FRotationMatrix(BaseRotation);
        FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
        FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
        FVector NormalizedVel = Velocity.GetSafeNormal2D();

        // get a cos(alpha) of forward vector vs velocity
        float ForwardCosAngle =
            FVector::DotProduct(ForwardVector, NormalizedVel);
        // now get the alpha and convert to degree
        float ForwardDeltaDegree =
            FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));

        // depending on where right vector is, flip it
        float RightCosAngle = FVector::DotProduct(RightVector, NormalizedVel);
        if (RightCosAngle < 0)
        {
            ForwardDeltaDegree *= -1;
        }

        return ForwardDeltaDegree;
    }

    return 0.f;
}

float UMathUtilStatics::CalculateAcceleration(
    const FVector& Velocity, float DeltaTime, EVelocityScaleType VelocityScale)
{
    float Scale;

    switch (VelocityScale)
    {
        case EVelocityScaleType::Meters: Scale = 100.f; break;
        case EVelocityScaleType::Kilometers: Scale = 100000.f; break;
        default: Scale = 1.f; break;
    }

    return Velocity.Size() / Scale / DeltaTime;
}
