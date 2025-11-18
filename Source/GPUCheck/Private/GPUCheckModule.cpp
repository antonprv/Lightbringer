// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

#include "GPUCheckModule.h"

#define LOCTEXT_NAMESPACE "FGPUCheckModule"

int32 FGPUCheckModule::GetTotalVRAM()
{
#if PLATFORM_WINDOWS
    DXGI_QUERY_VIDEO_MEMORY_INFO Info = GetVideoMemoryInfo();
    if (Info.Budget > 0)
    {
        return static_cast<int32>(Info.Budget / 1024 / 1024);
    }
#endif
    return FallbackTotalVRAMMB;
}

int32 FGPUCheckModule::GetUsedVRAM()
{
#if PLATFORM_WINDOWS
    DXGI_QUERY_VIDEO_MEMORY_INFO Info = GetVideoMemoryInfo();
    if (Info.CurrentUsage > 0)
    {
        return static_cast<int32>(Info.CurrentUsage / 1024 / 1024);
    }
#endif
    return FallbackUsedVRAMMB;
}

DXGI_QUERY_VIDEO_MEMORY_INFO FGPUCheckModule::GetVideoMemoryInfo()
{
    DXGI_QUERY_VIDEO_MEMORY_INFO VideoMemoryInfo = {};
#if PLATFORM_WINDOWS
    IDXGIFactory4* PFactory = nullptr;
    if (SUCCEEDED(
            CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&PFactory)) &&
        PFactory)
    {
        IDXGIAdapter3* Adapter = nullptr;
        if (SUCCEEDED(PFactory->EnumAdapters(
                0, reinterpret_cast<IDXGIAdapter**>(&Adapter))) &&
            Adapter)
        {
            if (FAILED(Adapter->QueryVideoMemoryInfo(
                    0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &VideoMemoryInfo)))
            {
                // Query failed, will fallback
                FMemory::Memzero(&VideoMemoryInfo, sizeof(VideoMemoryInfo));
            }
            Adapter->Release();
        }
        PFactory->Release();
    }
#endif
    return VideoMemoryInfo;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGPUCheckModule, GPUCheck);
