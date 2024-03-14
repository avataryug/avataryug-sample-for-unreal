// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AvataryugDemo : ModuleRules
{
	public AvataryugDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicDependencyModuleNames.AddRange(new string[] { "Core","CoreUObject", "Engine", "InputCore", "HTTP", "Json","glTFRuntime", "JsonUtilities", 
		"Paper2D", "SlateCore" ,"OpenSSL","Avataryug","glTFRuntimeDraco"});

        Definitions.Add("AES_KEY=1");
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
