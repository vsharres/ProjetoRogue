// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProtuX : ModuleRules
{
	public ProtuX(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});

		PrivateDependencyModuleNames.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] { "ProtuX/Public", "ProtuX/Private" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
	}
}
