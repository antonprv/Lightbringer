// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "/Libraries/Shapes/2D/CircleShape.ush"

// inputs: NumSides, NumRepeats, bIs3DMovement, Time, Speed, Center, Radius, UV, Size

float Result = 0;

CircleShape Circle;

// Windows-like movement
if (!bIs3DMovement && NumRepeats == 0)
{
    for (int i = 0; i < NumSides; ++i)
    {
        float Angle = (i / NumSides) * (Time * Speed) * 3.14;
        float2 SinAngle = float2(cos(Angle), sin(Angle));
        float2 Pos = Center + Radius * SinAngle;

        Result += Circle.Draw(Pos, UV, Size);
    }
}
else if (bIs3DMovement && NumRepeats == 0)
{
    for (int i = 0; i < NumSides; ++i)
    {
        float Angle = (i / NumSides) * (Time * Speed) * 3.14;
        float2 SinAngle = float2(cos(1 - Angle), sin(3 * Angle));
        float2 Pos = Center + Radius * SinAngle;

        Result += Circle.Draw(Pos, UV, Size);
    }
}

// Array movement
if (!bIs3DMovement && NumRepeats > 0)
{
    for (int i = 0; i < NumSides; ++i)
    {
        for(int j = 0; j < NumRepeats; ++j)
        {
            float Angle = (i / NumSides) * (Time * Speed) * 3.14;
            float2 SinAngle = float2(cos(Angle), sin(Angle));
            float2 Pos = Center + (j / NumRepeats) * Radius * SinAngle;

            Result += Circle.Draw(Pos, UV, Size);
        }
    }
}
else if (bIs3DMovement && NumRepeats > 0)
{
    for (int i = 0; i < NumSides; ++i)
    {
        for(int j = 0; j < NumRepeats; ++j)
        {
            float Angle = (i / NumSides) * (Time * Speed) * 3.14;
            float2 SinAngle = float2(cos(1 - Angle), sin(3 * Angle));
            float2 Pos = Center + (j / NumRepeats) * Radius * SinAngle;

            Result += Circle.Draw(Pos, UV, Size);
        }
    }
}

return Result;