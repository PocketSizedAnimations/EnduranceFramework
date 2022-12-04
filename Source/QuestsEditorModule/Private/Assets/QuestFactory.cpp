// Copyright (c) 2022 Pocket Sized Animations


#include "Assets/QuestFactory.h"
#include "QuestsEditorModule.h"
#include "Quests/Quest.h"

#define LOCTEXT_NAMESPACE "QuestEditorModule" 

UQuestFactory::UQuestFactory(const FObjectInitializer& ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UQuest::StaticClass();
}

UObject* UQuestFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UQuest* NewObjectAsset = NewObject<UQuest>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

uint32 UQuestFactory::GetMenuCategories() const
{
	return FModuleManager::Get().GetModuleChecked<FQuestsEditorModule>("QuestsEditorModule").AssetCategory;
}

FText UQuestFactory::GetDisplayName() const
{
	return LOCTEXT("QuestObject", "Quest");
}

FString UQuestFactory::GetDefaultNewAssetName() const
{
	return FString(TEXT("NewQuest"));
}

#undef LOCTEXT_NAMESPACE

FText FAssetTypeActions_Quest::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Quest", "Quest Blueprint");

}

FColor FAssetTypeActions_Quest::GetTypeColor() const
{
	return FColor(151, 255, 71);
}

UClass* FAssetTypeActions_Quest::GetSupportedClass() const
{
	return UQuest::StaticClass();

}

uint32 FAssetTypeActions_Quest::GetCategories()
{
	return AssetCategory;
}


