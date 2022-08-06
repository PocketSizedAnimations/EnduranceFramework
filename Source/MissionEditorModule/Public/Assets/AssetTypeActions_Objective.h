// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class MISSIONEDITORMODULE_API FAssetTypeActions_Objective : public FAssetTypeActions_Base
{

	friend class MissionEditorModule;

public:
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	/** Indicates the category used for Dialogues */
	uint32 AssetCategory;

public:
	FAssetTypeActions_Objective(uint32 InAssetCategory) : AssetCategory(InAssetCategory) {}
};
