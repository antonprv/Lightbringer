// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

// #include "/Libraries/Shapes/3D/Operands/RenderOperand.ush"

// Inputs:  Part
//          WorldPosition, ObjectPosition
//          CameraVector,
//          Radius
//          Location, Rotation, Scale
//          StepSize, NumRaySteps,
//          OverlapDetectionThreshold
//          Color, LightDirection, AmbientLight, ShadowContrast, 
//          RimStrength, RimContrast, RimColor,
//          SpecularSoftness, SpecularColor,
<<<<<<< Updated upstream
=======
//          Radius, BevelRadius, HalfHeight
//          Location, Rotation, Scale
>>>>>>> Stashed changes

float3 RenderOpPosition = WorldPosition - ObjectPosition;

// Visual parameters
URenderOperand RenderOp;
FDrawParams DrawParams;
FPBRParams PBRParams;

DrawParams.ViewRayOrigin = 1 - (CameraVector - RenderOpPosition);
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

RenderOp.Color = Color;

RenderOp.DrawParams = DrawParams;
RenderOp.PBRParams = PBRParams;

RenderOp.InPart = Part;

FTransform Transform;

Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

RenderOp.Transform = Transform;
RenderOp.Radius = Radius;

FTransform Transform;
Transform.Location = Location;
Transform.Rotation = Rotation;
Transform.Scale = Scale;

RenderOp.Transform = Transform;

// Draw call
return RenderOp.Draw();