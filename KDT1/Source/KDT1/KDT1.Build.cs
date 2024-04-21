// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class KDT1 : ModuleRules
{
	public KDT1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core"
			, "CoreUObject"
			, "Engine"
			, "InputCore"
			, "UMG"
			, "AIModule"
			, "EnhancedInput"
			, "NavigationSystem"
			, "Niagara"
			, "LevelSequence"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent", "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
