// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

using UnrealBuildTool;
using System.Collections.Generic;

public class LightbringerTarget : TargetRules
{
	public LightbringerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;

        ExtraModuleNames.AddRange( new string[] { "Lightbringer" } );
	}
}
