#include "/Library/Functions/Shapes.ush"

// inputs: NumSides, Center, Radius, UV, Size

float Result = 0;

DrawCircle Circle;

for (int i = 0; i < NumSides; ++i)
{
    float Angle = (float(i) / NumSides) * 2 * 3.14;

    float2 SinAngle = float2(cos(Angle), sin(Angle));

    float2 Pos = Center + Radius * SinAngle;

    result += Circle.Draw(Pos, UV, Size);
}

return Result;