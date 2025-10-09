float2 tiled_uv = frac(uv * tiling);

float positioned = length(position - tiled_uv);

if (!is_soft)
{
    return positioned < size;
}
else
{
    return pow(positioned, size);
}