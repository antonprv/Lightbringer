// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

 //#include "/Libraries/Shapes/3D/Estimators/SphereEstimator.ush"

// Inputs:  WorldPosition, ObjectPosition, CameraVector
//          Radius
//          Location, Rotation, Scale

// Outputs  OutWorldPosition, OutObjectPosition, OutCameraVector
//          Part
//          OutLocation, OutRotation, OutScale
//          OutRadius

// All inputs are just passed further and exist for convenience

// Node Outputs:
OutWorldPosition = WorldPosition;
OutObjectPosition = ObjectPosition;
OutCameraVector = CameraVector;

OutLocation = Location;
OutRotation = OutRotation;
OutScale = Scale;

OutRadius = Radius;

// Type output
return USphereEstimator::GetType();