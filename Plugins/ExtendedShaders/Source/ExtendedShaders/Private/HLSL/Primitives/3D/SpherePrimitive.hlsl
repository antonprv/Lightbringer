#include "/Libraries/Shapes/3D/SphereShape.ush"

// Inputs: WorldPosition, ObjectPosition
// CameraVector, StepSize, NumRaySteps, CenterPosition, Radius, OverlapDetectionThreshold
// Color, LightDirection, AmbientLight, ShadowContrast, 
// RimStrength, RimContrast, RimColor,
// SpecularSoftness, SpecularColor
// Location, Rotation, Scale

float3 SpherePosition = WorldPosition - ObjectPosition;

// Visual parameters
USphereShape Sphere;
FDrawParams DrawParams;
FPBRParams PBRParams;

DrawParams.ViewRayOrigin = 1 - (CameraVector - SpherePosition);
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

Sphere.Color = Color;
Sphere.Radius = Radius;

Sphere.DrawParams = DrawParams;
Sphere.SpherePBR = PBRParams;

// Transform parameters
FTransform Transform;
Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

Sphere.Transform = Transform;

// Draw call
return Sphere.Draw();