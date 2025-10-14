// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

float2 SteppedMask = ceil(UV * Steps) / Steps;

float SinAnimation = sin(Time * Speed);

if (bIsGradient)
{
    return SteppedMask - SinAnimation;
}
else
{
    return trunc(SteppedMask - SinAnimation);
}