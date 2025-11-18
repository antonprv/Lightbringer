// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "/Libraries/Shapes/3D/Estimators/BoxEstimator.ush"

<<<<<<< Updated upstream
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
=======
// Inputs:  WorldPosition, ObjectPosition, CameraVector
//          Location, Rotation, Scale
//          BevelRadius
// Outputs: OutWorldPosition, OutObjectPosition, OutCameraVector
//          OutBevelRadius
//          OutLocation, OutRotation, OutScale

// All inputs are just passed further and exist for convenience
>>>>>>> Stashed changes

SomeOutput = float3(1, 0, 0);

<<<<<<< Updated upstream
// Draw call
return Box.GetDistance();
=======
OutBevelRadius = BevelRadius;

OutLocation = Location;
OutRotation = Rotation;
OutScale = Scale;

// Send type
return UBoxEstimator::GetType();
>>>>>>> Stashed changes
