// Copyright (c) 2022 Pocket Sized Animations

using UnrealBuildTool;
using System.Collections.Generic;

public class GameFrameworksTarget : TargetRules
{
	public GameFrameworksTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "GameFrameworks", "ExtendedAIModule","FirstPersonModule", "InteractionsModule", "InventoryModule", "EquipmentModule", "HealthAndStaminaModule","MissionModule", "WeaponsModule"} );
	}
}
