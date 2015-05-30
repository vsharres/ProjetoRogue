// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjetoRogue : ModuleRules
{
	public ProjetoRogue(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});

		PrivateDependencyModuleNames.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] { "ProjetoRogue/Public", "ProjetoRogue/Private" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
	}
}
