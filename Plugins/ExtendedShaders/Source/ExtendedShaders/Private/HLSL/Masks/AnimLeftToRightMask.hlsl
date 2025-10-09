float2 stepped_mask = ceil(uv * steps) / steps;

float sin_animation = sin(time * speed);

if (is_gradient)
{
    return stepped_mask - sin_animation;
}
else
{
    return trunc(stepped_mask - sin_animation);
}