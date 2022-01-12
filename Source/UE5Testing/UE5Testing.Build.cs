// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5Testing : ModuleRules
{
	public UE5Testing(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Niagara", "LiveCoding" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });
		bUseUnity = true;
	}
}
