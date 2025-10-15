// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "/Libraries/Shapes/3D/Estimators/BoxEstimator.ush"

// Inputs:WorldPosition, ObjectPosition, CameraVector
// Location, Rotation, Scale
// BevelRadius

float3 BoxPosition = WorldPosition - ObjectPosition;

// Visual parameters
UBoxEstimator Box;

Box.RayOrigin = 1 - (CameraVector - BoxPosition);

Box.BevelRadius = BevelRadius;

// Transform parameters
FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

Box.Transform =
Transform;

SomeOutput = float3(1, 0, 0);

// Draw call
return Box.GetDistance();