// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "/Libraries/Shapes/CompoundShapes/Operands/AddOperand.ush"

// Inputs:WorldPosition, ObjectPosition
// CameraVector
// Location, Rotation, Scale
// BevelRadius, ChamferRadius, DetectionRadius
// ShapeA, ShapeB

float3 AddOpPosition = WorldPosition - ObjectPosition;

// Visual parameters
UAddOperand AddOp;

AddOp.RayOrigin = 1 - (CameraVector - AddOpPosition);

AddOp.ShapeADistance = ShapeA;
AddOp.ShapeBDistance = ShapeB;

AddOp.Color = Color;
AddOp.BevelRadius = BevelRadius;
AddOp.ChamferRadius = ChamferRadius;
AddOp.DetectionRadius = DetectionRadius;

// Transform parameters
FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

AddOp.Transform = Transform;

return AddOp.GetDistance();