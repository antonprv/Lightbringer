// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExtendedShaders : ModuleRules
{
    public ExtendedShaders(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);

        PrivateIncludePaths.AddRange(
            new string[] {
                "ExtendedShaders/Private",
                "ExtendedShaders/Private/HLSL",
                "ExtendedShaders/Private/HLSL/Masks",
                "ExtendedShaders/Private/HLSL/Shapes",
                "ExtendedShaders/Private/HLSL/Libraries",
                "ExtendedShaders/Private/HLSL/Libraries/Functions"
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "RenderCore",
                "Projects"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
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
