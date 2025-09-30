// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LBHUD.generated.h"

/**
 *
 */
UCLASS()
class LIGHTBRINGER_API ALBHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void DrawHUD() override;

private:
    void DrawCrossHair();
};
