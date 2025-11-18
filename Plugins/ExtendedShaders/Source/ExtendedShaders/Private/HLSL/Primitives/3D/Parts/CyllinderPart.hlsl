// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

//#include "/Libraries/Shapes/CompoundShapes/Estimators/CyllinderEstimator.ush"

// Inputs:  WorldPosition, ObjectPosition, CameraVector
//          Location, Rotation, Scale,
//          HalfHeight, BevelRadius, Radius
// Outputs: OutWorldPosition, OutObjectPosition, OutCameraVector
//          OutHalfHeight, OutBevelRadius, OutRadius
//          OutLocation, OutRotation, OutScale

// All inputs are just passed further and exist for convenience

// Node Outputs:
OutWorldPosition = WorldPosition;
OutObjectPosition = ObjectPosition;
OutCameraVector = CameraVector;

OutHalfHeight = HalfHeight;
OutBevelRadius = BevelRadius;
OutRadius = Radius;

OutLocation = Location;
OutRotation = Rotation;
OutScale = Scale;

// Send type
return UCyllinderEstimator::GetType();