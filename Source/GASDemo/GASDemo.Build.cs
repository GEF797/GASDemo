// Copyright G.E.FC 2024

using UnrealBuildTool;

public class GASDemo : ModuleRules
{
	public GASDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "GASDemo"
            }
        );


        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", });

		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "AdvancedGASSystem", "GameplayAbilities", "GameplayTags" ,"NetworkReplayStreaming",
                "NetCore","EnhancedInput"});


        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
