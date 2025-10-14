// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

using System.IO;
using UnrealBuildTool;

public class Lightbringer : ModuleRules
{
    public Lightbringer(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);

        // Correct include paths (relative to ModuleDirectory)
        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Public"),
            // Data paths
            Path.Combine(ModuleDirectory, "Public", "Data"),
            // Dev paths
            Path.Combine(ModuleDirectory, "Public", "Dev"),
            Path.Combine(ModuleDirectory, "Public", "Dev", "TestCoreGameplay"),
            // Gameplay paths
            Path.Combine(ModuleDirectory, "Public", "Gameplay"),
            Path.Combine(ModuleDirectory, "Public", "Gameplay", "Components"),
            Path.Combine(ModuleDirectory, "Public", "Gameplay", "Game"),
            Path.Combine(ModuleDirectory, "Public", "Gameplay", "Subsystems"),
            // View paths
            Path.Combine(ModuleDirectory, "Public", "View"),
            Path.Combine(ModuleDirectory, "Public", "View", "Actors"),
            Path.Combine(ModuleDirectory, "Public", "View", "Components"),
            Path.Combine(ModuleDirectory, "Public", "View", "Player"),
            Path.Combine(ModuleDirectory, "Public", "View", "Player", "Interfaces"),
            Path.Combine(ModuleDirectory, "Public", "View", "Rendering"),
            Path.Combine(ModuleDirectory, "Public", "View", "Subsystems"),
            Path.Combine(ModuleDirectory, "Public", "View", "UI"),
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Private")
        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "RenderCore",
            "SimpleInput",
            "ExtendedControlStates",
            "FakeShadow"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            //
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            //
        });

        PublicIncludePaths.AddRange(new string[] {
            "Lightbringer/Public/Data",
            "Lightbringer/Public/Dev",
            "Lightbringer/Public/Gameplay",
            "Lightbringer/Public/View"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
