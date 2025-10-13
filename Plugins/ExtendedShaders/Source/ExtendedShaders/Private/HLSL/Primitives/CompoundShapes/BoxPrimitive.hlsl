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
FPBRParams RenderParams;

DrawParams.ViewRayOrigin = 1 - (CameraVector - BoxPosition);
DrawParams.RayStep = CameraVector * -1;
DrawParams.StepSize = StepSize;
DrawParams.NumSteps = NumRaySteps;
DrawParams.OverlapDetectionThreshold = OverlapDetectionThreshold;

RenderParams.LightDirection = LightDirection;
RenderParams.AmbientLight = AmbientLight;
RenderParams.ShadowContrast = ShadowContrast;

RenderParams.ViewDirection = CameraVector;

RenderParams.RimStrength = RimStrength;
RenderParams.RimContrast = RimContrast;
RenderParams.RimColor = RimColor;

RenderParams.SpecularSoftness = SpecularSoftness;
RenderParams.SpecularColor = SpecularColor;

Box.Color = Color;
Box.BevelRadius = BevelRadius;

Box.DrawParams = DrawParams;
Box.BoxPBR = RenderParams;

// Transform parameters
FTransform BoxTransform;

BoxTransform.Location = Location;
BoxTransform.Rotation = Rotation;
BoxTransform.Scale = Scale;

Box.Transform = BoxTransform;

// Draw call
return Box.Draw();