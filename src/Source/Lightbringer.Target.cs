// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

using UnrealBuildTool;
using System.Collections.Generic;

public class LightbringerTarget : TargetRules
{
	public LightbringerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Lightbringer" } );
	}
}
