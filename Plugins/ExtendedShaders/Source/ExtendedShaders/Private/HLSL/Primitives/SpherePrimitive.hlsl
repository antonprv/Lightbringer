#include "/Libraries/Shapes/SphereShape.ush"

// Inputs: bIsMaskedByGeometry, WorldPosition, ObjectPosition
// CameraVector, NumRaySteps, Position, Radius, OverlapDetectionThreshold
// Color

float3 SpherePosition;

if (bIsMaskedByGeometry)
{
    SpherePosition = WorldPosition;
}
else if (!bIsMaskedByGeometry)
{
    SpherePosition = WorldPosition - ObjectPosition;
}

SphereShape Sphere;
SphereDrawParams Params;

Params.RayOrigin = CameraVector - SpherePosition;
Params.RayStep = CameraVector * 1;
Params.NumSteps = NumRaySteps;
Params.OverlapDetectionThreshold = OverlapDetectionThreshold;

Sphere.Color = Color;
Sphere.Radius = Radius;
Sphere.Position = Position;
Sphere.DrawParams = Params;

return Sphere.Draw();