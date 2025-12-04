// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class Lightbringer : ModuleRules
{
    public Lightbringer(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "RenderCore",
            "AnimationBudgetAllocator",
            "AnimationSharing",
            "AnimGraphRuntime",
            "SimpleInput",
            "ExtendedControlStates",
            "FakeShadow"
        });

        PrivateDependencyModuleNames.Add("GPUCheck");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
