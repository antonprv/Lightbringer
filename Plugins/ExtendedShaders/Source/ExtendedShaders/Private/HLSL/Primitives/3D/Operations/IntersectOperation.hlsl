// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "/Libraries/Shapes/3D/Operands/IntersectOperand.ush"

// Inputs:WorldPosition, ObjectPosition
// CameraVector
// Location, Rotation, Scale
// BevelRadius, ChamferRadius, DetectionRadius
// ShapeA, ShapeB

float3 IntersectOpPosition = WorldPosition - ObjectPosition;

// Visual parameters
UIntersectOperand IntersectOp;

IntersectOp.RayOrigin = 1 - (CameraVector - IntersectOpPosition);

IntersectOp.ShapeADistance = ShapeA;
IntersectOp.ShapeBDistance = ShapeB;

IntersectOp.Color = Color;
IntersectOp.BevelRadius = BevelRadius;
IntersectOp.ChamferRadius = ChamferRadius;
IntersectOp.DetectionRadius = DetectionRadius;

// Transform parameters
FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

IntersectOp.Transform = Transform;

return IntersectOp.GetDistance();