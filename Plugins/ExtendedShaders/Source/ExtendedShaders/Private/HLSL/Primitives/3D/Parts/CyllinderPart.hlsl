// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "/Libraries/Shapes/CompoundShapes/Estimators/CyllinderEstimator.ush"

// Inputs: WorldPosition, ObjectPosition, CameraVector
// Location, Rotation, Scale,
// HalfHeight, BevelRadius, Radius

float3 CyllinderPosition = WorldPosition - ObjectPosition;

// Render parameters
UCyllinderEstimator Cyllinder;

Cyllinder.RayOrigin = 1 - (CameraVector - CyllinderPosition);

Cyllinder.Color = Color;

Cyllinder.Radius = Radius;
Cyllinder.HalfHeight = HalfHeight;
Cyllinder.BevelRadius = BevelRadius;

// Transform parameters
FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

Cyllinder.Transform = Transform;

// Draw call
return Cyllinder.GetDistance();