// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

// Inputs:  InTexture2D
// Outputs: Dimensions

uint3 Dimensions;

InTexture2D.GetDimensions(0, Dimensions.x, Dimensions.y, Dimensions.z);

return float2(Dimensions.xy);