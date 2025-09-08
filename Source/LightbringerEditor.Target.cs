// You can use this project non-commercially for educational purposes, any commercial use, derivative commercial use is strictly prohibited

using UnrealBuildTool;
using System.Collections.Generic;

public class LightbringerEditorTarget : TargetRules
{
	public LightbringerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Lightbringer" } );
	}
}
