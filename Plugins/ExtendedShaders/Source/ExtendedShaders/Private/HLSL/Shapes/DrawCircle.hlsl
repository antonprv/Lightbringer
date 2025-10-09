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