// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_SplitGuys : ModuleRules
{
	public Project_SplitGuys(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ApexDestruction", "AIModule", "GameplayTasks", "NavigationSystem" });
	}
}
