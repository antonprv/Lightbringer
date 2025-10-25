// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

 //#include "/Libraries/Shapes/3D/Estimators/SphereEstimator.ush"

// Inputs:  WorldPosition, ObjectPosition, CameraVector
//          Radius
//          Location, Rotation, Scale

// Outputs  OutWorldPosition, OutObjectPosition, OutCameraVector
//          OutRadius
//          OutLocation, OutRotation, OutScale
//          Part

// Inputs:
float3 SpherePosition = WorldPosition - ObjectPosition;

USphereEstimator Sphere;

Sphere.RayOrigin = 1 - (CameraVector - SpherePosition);

Sphere.Radius = Radius;

FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

Sphere.Transform = Transform;

// Additional outputs
OutWorldPosition = WorldPosition;
OutObjectPosition = ObjectPosition;
OutCameraVector = CameraVector;

OutRadius = Radius;

OutLocation = Location;
OutRotation = Rotation;
OutScale = Scale;

// Type output
return Sphere.GetType();