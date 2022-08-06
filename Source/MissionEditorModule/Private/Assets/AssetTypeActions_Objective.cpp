// Copyright (c) 2022 Pocket Sized Animations


#include "Assets/AssetTypeActions_Objective.h"
#include "MissionModule/Public/Objectives/Objective.h"
#include "Editors/MissionEditor.h"

FText FAssetTypeActions_Objective::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Objective", "Objective Blueprint");
}

FColor FAssetTypeActions_Objective::GetTypeColor() const
{
	return FColor(151, 255, 71);
}

UClass* FAssetTypeActions_Objective::GetSupportedClass() const
{
	return UMissionObjective::StaticClass();
}

void FAssetTypeActions_Objective::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto Object : InObjects)
	{
		auto NewAsset = Cast<UMissionObjective>(Object);
		if (NewAsset != nullptr)
		{
			TSharedRef<FMissionEditor> NewEditor(new FMissionEditor());
			NewEditor->InitEditor(Mode, EditWithinLevelEditor, NewAsset);
		}
	}
}

uint32 FAssetTypeActions_Objective::GetCategories()
{
	return AssetCategory;
}
