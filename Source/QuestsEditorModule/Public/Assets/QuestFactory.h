// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"
#include "QuestFactory.generated.h"


/**
 * 
 */
UCLASS()
class QUESTSEDITORMODULE_API UQuestFactory : public UFactory
{
	GENERATED_BODY()
public:

	UQuestFactory(const FObjectInitializer& ObjectInitializer);
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface

	virtual uint32 GetMenuCategories() const override;
	virtual FText GetDisplayName() const override;
	virtual FString GetDefaultNewAssetName() const override;
	
};

/**
 *
 */
class QUESTSEDITORMODULE_API FAssetTypeActions_Quest : public FAssetTypeActions_Base
{

	friend class QuestEditorModule;

public:
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	//virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	/** Indicates the category used for Dialogues */
	uint32 AssetCategory;

public:
	FAssetTypeActions_Quest(uint32 InAssetCategory) : AssetCategory(InAssetCategory) {}
};
