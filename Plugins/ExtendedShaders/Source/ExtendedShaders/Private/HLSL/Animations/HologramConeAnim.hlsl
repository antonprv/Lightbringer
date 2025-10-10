#include "/Libraries/Shapes/CircleShape.ush"

// inputs: NumSides, NumRepeats, Time, Speed, Center, Radius, UV, Size, ColorStart, ColorEnd, WhiteBrightness

float Result = 0;

CircleShape Circle;

float TimeChange = sin(Time * Speed);

for (int i = 0; i < NumSides; ++i)
{
    for( int j = 0; j < NumRepeats; ++j)
    {
        float Angle = (float(i) / NumSides) * TimeChange * (3.14 * 2);
        float2 SinAngle = float2(sin(1 - Angle) - sin(Time),
                                         cos(1 - Angle) - sin(Time));

        float2 Pos = Center + (j / NumRepeats) * Radius * SinAngle;

        Result += Circle.Draw(Pos, UV, Size);
    }
}

Result *= WhiteBrightness;

float3 OutColor = lerp(ColorStart, ColorEnd, TimeChange);

return float4(OutColor.x * Result, OutColor.y * Result, OutColor.z * Result, Result);