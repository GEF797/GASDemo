// Copyright G.E.FC 2024

using UnrealBuildTool;
using System.Collections.Generic;

public class GASDemoEditorTarget : TargetRules
{
	public GASDemoEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("GASDemo");
	}
}
