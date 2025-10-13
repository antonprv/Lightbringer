#include "/Libraries/Shapes/3D/BoxShape.ush"

// Inputs:WorldPosition, ObjectPosition
// CameraVector, StepSize, NumRaySteps,
// Location, Rotation, Scale
// BevelRadius,
// OverlapDetectionThreshold
// Color, LightDirection, AmbientLight, ShadowContrast, 
// RimStrength, RimContrast, RimColor,
// SpecularSoftness, SpecularColor

float3 BoxPosition = WorldPosition - ObjectPosition;

// Visual parameters
UBoxShape Box;
FDrawParams DrawParams;
FPBRParams PBRParams;

DrawParams.ViewRayOrigin = 1 - (CameraVector - BoxPosition);
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

Box.Color = Color;
Box.BevelRadius = BevelRadius;

Box.DrawParams = DrawParams;
Box.PBRParams = PBRParams;

// Transform parameters
FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

Box.Transform = Transform;

// Draw call
return Box.Draw();