// Copyright Anton Piruev. All Rights Reserved. 
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

float2 BlocksCoord =
    frac(float2(UV.x * Tiling.x + Offset.x, UV.y* Tiling.y + Offset.y));

if (BlocksCoord.x >= Dimension.x || BlocksCoord.x <= -Dimension.x ||
    BlocksCoord.y >= Dimension.y || BlocksCoord.y <= -Dimension.y)
{
    return (1);
}
else
{
    return (0);
}