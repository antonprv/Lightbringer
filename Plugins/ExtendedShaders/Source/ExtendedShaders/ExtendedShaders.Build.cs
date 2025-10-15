// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ExtendedShaders : ModuleRules
{
    public ExtendedShaders(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);

        // Correct include paths (relative to ModuleDirectory)
        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public", "Animations"),
            Path.Combine(ModuleDirectory, "Public", "Primitives"),
            Path.Combine(ModuleDirectory, "Public", "Primitives", "2D"),
            Path.Combine(ModuleDirectory, "Public", "Primitives", "3D"),
            Path.Combine(ModuleDirectory, "Public", "Primitives", "3D", "Operations"),
            Path.Combine(ModuleDirectory, "Public", "Primitives", "3D", "Parts"),
            Path.Combine(ModuleDirectory, "Public", "Utils")
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Private"),
            Path.Combine(ModuleDirectory, "Private", "HLSL"),
            Path.Combine(ModuleDirectory, "Private", "HLSL", "Animations"),
            Path.Combine(ModuleDirectory, "Private", "HLSL", "Primitives"),
            Path.Combine(ModuleDirectory, "Private", "HLSL", "Libraries"),
            Path.Combine(ModuleDirectory, "Private", "HLSL", "Libraries", "Shapes"),
            Path.Combine(ModuleDirectory, "Private", "HLSL", "Libraries", "Graphics")
        });

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "RenderCore",
                "Projects",
                "RHI"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore"
            }
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

    }
}
