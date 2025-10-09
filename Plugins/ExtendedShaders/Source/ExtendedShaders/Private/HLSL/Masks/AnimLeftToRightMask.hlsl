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