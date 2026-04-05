// Copyright Anton Piruev. All Rights Reserved.
// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "Data/LBHealthRegenProfile.h"

void ULBHealthRegenProfile::PostLoad()
{
    Super::PostLoad();

    if (RegenCurve)
    {
        CachedCurveValues.Empty(100);
        for (float t = 0; t <= 10; t += 0.1f)
            CachedCurveValues.Add(RegenCurve->GetFloatValue(t));
    }
}

 float ULBHealthRegenProfile::GetCachedRegenValue(float Time) const
 {
     const int32 Index = FMath::Min(static_cast<int32>(Time * 10),
     CachedCurveValues.Num() - 1); return
     CachedCurveValues.IsValidIndex(Index) ? CachedCurveValues[Index] : 0.f;
 }
