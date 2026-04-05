// You can use this project non-commercially for educational purposes, any
// commercial use, derivative commercial use is strictly prohibited

using UnrealBuildTool;

public class GPUCheck: ModuleRules
{
    public GPUCheck(ReadOnlyTargetRules Target) : base(Target)

    {
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine"
        });

        PublicIncludePathModuleNames.Add("RHI");

        if ((Target.IsInPlatformGroup(UnrealPlatformGroup.Windows)))
        {
            // Uses DXGI to query GPU hardware
            // This is what will allow us to get GPU usage statistics at runtime
            PublicSystemLibraries.Add("DXGI.lib");
        }
    }
}
