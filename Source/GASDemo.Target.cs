// Copyright G.E.FC 2024

using UnrealBuildTool;
using System.Collections.Generic;

public class GASDemoTarget : TargetRules
{
	public GASDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("GASDemo");
	}
}
