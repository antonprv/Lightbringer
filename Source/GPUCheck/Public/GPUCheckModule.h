// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "Windows/WindowsHWrapper.h"

THIRD_PARTY_INCLUDES_START
#include "Windows/AllowWindowsPlatformTypes.h"
#include "dxgi1_4.h"
#include "Windows/HideWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_END

class GPUCHECK_API FGPUCheckModule : public IModuleInterface
{
public:
    static int32 GetTotalVRAM();
    static int32 GetUsedVRAM();

private:
    static DXGI_QUERY_VIDEO_MEMORY_INFO GetVideoMemoryInfo();

    // Default to artifial 3GB VRAM GPU in any undefined behaviour
    // and act as if its VRAM is almost full.
    static constexpr int32 FallbackTotalVRAMMB = 3072;
    static constexpr int32 FallbackUsedVRAMMB = 2800;
};