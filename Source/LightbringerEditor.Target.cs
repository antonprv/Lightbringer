// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

using System.Collections.Generic;
using UnrealBuildTool;
using static UnrealBuildTool.ModuleRules;

public class LightbringerEditorTarget : TargetRules
{
	public LightbringerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        DefaultBuildSettings = BuildSettingsVersion.V4;

        bLegacyPublicIncludePaths = true;
        ShadowVariableWarningLevel = WarningLevel.Warning;
        bLegacyParentIncludePaths = true;
        CppStandard = CppStandardVersion.Default;

        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;

        ExtraModuleNames.AddRange( new string[] { "Lightbringer" } );
	}
}
