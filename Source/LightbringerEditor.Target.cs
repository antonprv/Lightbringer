// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

using System.Collections.Generic;
using UnrealBuildTool;
using static UnrealBuildTool.ModuleRules;

public class LightbringerEditorTarget : TargetRules
{
	public LightbringerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        DefaultBuildSettings = BuildSettingsVersion.V6;

        bLegacyPublicIncludePaths = true;
        bOverrideBuildEnvironment = true;
        CppCompileWarningSettings.ShadowVariableWarningLevel = WarningLevel.Warning;
        bLegacyParentIncludePaths = true;
        CppStandard = CppStandardVersion.Default;

        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange( new string[] { "Lightbringer" } );
	}
}
