// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "UI/LBHUD.h"

#include "Engine/Canvas.h"

void ALBHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawCrossHair();
}

void ALBHUD::DrawCrossHair()
{
    FVector2D Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

    float HalfLIneSize = 10.f;
    float LineThickness = 2.f;

    DrawLine(                     //
        Center.X - HalfLIneSize,  //
        Center.Y - HalfLIneSize,  //
        Center.X + HalfLIneSize,  //
        Center.Y + HalfLIneSize,  //
        FLinearColor::Blue,       //
        LineThickness             //
    );

    DrawLine(                     //
        Center.X + HalfLIneSize,  //
        Center.Y - HalfLIneSize,  //
        Center.X - HalfLIneSize,  //
        Center.Y + HalfLIneSize,  //
        FLinearColor::Blue,       //
        LineThickness             //
    );
}
