float d = length(Coord - UV);

if (!IsSoft)
{
    return d < Size;
}
else
{
    return pow(d, Size) * Dist;
}