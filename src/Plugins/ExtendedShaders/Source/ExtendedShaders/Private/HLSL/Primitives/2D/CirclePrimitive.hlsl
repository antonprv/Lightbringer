// Copyright Anton Piruev. All Rights Reserved. 
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

float2 TiledUV = frac(UV * Tiling);

float Positioned = length(Position - TiledUV);

if (!bIsSoft)
{
    return Positioned < Size;
}
else
{
    return pow(Positioned, Size);
}