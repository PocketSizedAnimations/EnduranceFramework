// Copyright (c) 2022 Pocket Sized Animations

using System.IO;
using UnrealBuildTool;

public class ExtendedFirstPersonModule : ModuleRules
{
	public ExtendedFirstPersonModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] 
			{
                Path.Combine(ModuleDirectory, "Public")
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] 
			{
				
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InventoryModule",
				"WeaponsModule"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
			}
			);
	}
}
