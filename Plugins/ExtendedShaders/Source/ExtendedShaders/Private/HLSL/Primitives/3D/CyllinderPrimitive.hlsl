#include "/Libraries/Shapes/3D/CyllinderShape.ush"

// Inputs: bIsWorldSpace, WorldPosition, ObjectPosition
// CameraVector, StepSize, NumRaySteps, CenterPosition,
// Location, Rotation, Transform,
// HalfHeight, BevelRadius, Rotation
// OverlapDetectionThreshold
// Color, LightDirection, AmbientLight, ShadowContrast, 
// RimStrength, RimContrast, RimColor,
// SpecularSoftness, SpecularColor

float3 CyllinderPosition = WorldPosition - ObjectPosition;

// Render parameters
UCyllinderShape Cyllinder;
FDrawParams DrawParams;
FPBRParams PBRParams;

DrawParams.ViewRayOrigin = 1 - (CameraVector - CyllinderPosition);
DrawParams.RayStep = CameraVector * -1;
DrawParams.StepSize = StepSize;
DrawParams.NumSteps = NumRaySteps;
DrawParams.OverlapDetectionThreshold = OverlapDetectionThreshold;

PBRParams.LightDirection = LightDirection;
PBRParams.AmbientLight = AmbientLight;
PBRParams.ShadowContrast = ShadowContrast;

PBRParams.ViewDirection = CameraVector;

PBRParams.RimStrength = RimStrength;
PBRParams.RimContrast = RimContrast;
PBRParams.RimColor = RimColor;

PBRParams.SpecularSoftness = SpecularSoftness;
PBRParams.SpecularColor = SpecularColor;

Cyllinder.Color = Color;

Cyllinder.Radius = Radius;
Cyllinder.HalfHeight = HalfHeight;
Cyllinder.BevelRadius = BevelRadius;

Cyllinder.DrawParams = DrawParams;
Cyllinder.PBRParams = PBRParams;

// Transform parameters
FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

Cyllinder.Transform = Transform;

// Draw call
return Cyllinder.Draw();