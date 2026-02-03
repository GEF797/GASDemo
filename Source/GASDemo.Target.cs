// Copyright G.E.FC 2024

using UnrealBuildTool;
using System.Collections.Generic;

public class GASDemoTarget : TargetRules
{
	public GASDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("GASDemo");
	}
}
