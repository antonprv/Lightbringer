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
//          OutLocation, OutRotation, OutScale
//          OutRadius

// All inputs are just passed further and exist for convenience

// Additional outputs
OutWorldPosition = WorldPosition;
OutObjectPosition = ObjectPosition;
OutCameraVector = CameraVector;

<<<<<<< Updated upstream
OutRadius = Radius;

OutLocation = Location;
OutRotation = Rotation;
OutScale = Scale;

=======
OutLocation = Location;
OutRotation = OutRotation;
OutScale = Scale;

OutRadius = Radius;

>>>>>>> Stashed changes
// Type output
return USphereEstimator::GetType();