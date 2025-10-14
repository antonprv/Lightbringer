// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "/Libraries/Shapes/3D/Operands/SubtractOperand.ush"

// Inputs:WorldPosition, ObjectPosition
// CameraVector
// Location, Rotation, Scale
// BevelRadius, ChamferRadius, DetectionRadius
// ShapeA, ShapeB

float3 SubtractOpPosition = WorldPosition - ObjectPosition;

// Visual parameters
USubtractOperand SubtractOp;

SubtractOp.RayOrigin = 1 - (CameraVector - SubtractOpPosition);

SubtractOp.ShapeADistance = ShapeA;
SubtractOp.ShapeBDistance = ShapeB;

SubtractOp.Color = Color;
SubtractOp.BevelRadius = BevelRadius;
SubtractOp.ChamferRadius = ChamferRadius;
SubtractOp.DetectionRadius = DetectionRadius;

// Transform parameters
FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

SubtractOp.Transform = Transform;

return SubtractOp.GetDistance();