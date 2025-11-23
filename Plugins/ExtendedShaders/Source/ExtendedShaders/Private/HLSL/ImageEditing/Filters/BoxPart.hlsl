// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

//#include "/Libraries/Shapes/3D/Estimators/BoxEstimator.ush"

// Inputs:  WorldPosition, ObjectPosition, CameraVector
//          Location, Rotation, Scale
//          BevelRadius
// Outputs: OutWorldPosition, OutObjectPosition, OutCameraVector
//          OutBevelRadius
//          OutLocation, OutRotation, OutScale

// All inputs are just passed further and exist for convenience

// Node Outputs:
OutWorldPosition = WorldPosition;
OutObjectPosition = ObjectPosition;
OutCameraVector = CameraVector;

OutBevelRadius = BevelRadius;

OutLocation = Location;
OutRotation = Rotation;
OutScale = Scale;

// Send type
return UBoxEstimator::GetType();