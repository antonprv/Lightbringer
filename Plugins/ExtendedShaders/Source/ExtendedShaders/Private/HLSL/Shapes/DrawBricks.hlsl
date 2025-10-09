float2 tex = float2(uv.x * tiling.x + offset.x, uv.y* tiling.y + offset.y);
float2 tex_fractured = frac(tex);

if (tex_fractured.x >= dimension.x || tex_fractured.x <= -dimension.x ||
    tex_fractured.y >= dimension.y || tex_fractured.y <= -dimension.y)
{
    return (1);
}
else
{
    return (0);
}