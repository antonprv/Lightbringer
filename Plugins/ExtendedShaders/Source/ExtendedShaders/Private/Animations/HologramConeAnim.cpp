// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "HologramConeAnim.h"

UHologramConeAnim::UHologramConeAnim(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
{
    FriendlyName = "Hologram Cone";
    FriendlyCategory = "Animations";
    FriendlyDescription = "Holographic-looking pseudo3D scifi shader.";
    SetCategoryAndDescription();

    // inputs: NumSides, NumRepeats, Time, Speed, Center, Radius, UV, Size,
    // ColorStart, ColorEnd, WhiteBrightness

    NodeInputs.Add("NumSides", &NumSides);
    NodeInputs.Add("NumRepeats", &NumRepeats);

    NodeInputs.Add("Time", &Time);
    NodeInputs.Add("Speed", &Speed);

    NodeInputs.Add("Center", &Center);
    NodeInputs.Add("Radius", &Radius);
    NodeInputs.Add("UV", &UV);
    NodeInputs.Add("Size", &Size);

    NodeInputs.Add("ColorStart", &ColorStart);
    NodeInputs.Add("ColorEnd", &ColorEnd);
    NodeInputs.Add("ColorEnd", &ColorEnd);
    NodeInputs.Add("WhiteBrightness", &WhiteBrightness);

    NodeOutputType = CMOT_Float4;
    SetHLSLFilePath(
        "/Source/ExtendedShaders/Private/HLSL/Animations/HologramConeAnim.hlsl");
}