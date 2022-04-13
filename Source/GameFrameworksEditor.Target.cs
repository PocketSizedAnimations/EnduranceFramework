// Copyright (c) 2022 Pocket Sized Animations

using UnrealBuildTool;
using System.Collections.Generic;

public class GameFrameworksEditorTarget : TargetRules
{
	public GameFrameworksEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "GameFrameworks", "FirstPersonModule", "InteractionsModule", "InventoryModule", "EquipmentModule", "HealthAndStaminaModule" } );
	}
}
