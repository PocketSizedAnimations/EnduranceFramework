// Copyright (c) 2022 Pocket Sized Animations


#include "Assets/ObjectiveFactory.h"
#include "MissionEditorModule.h"
#include "MissionModule/Public/Objectives/Objective.h"

#define LOCTEXT_NAMESPACE "MissionEditorModule" 

UObjectiveFactory::UObjectiveFactory(const FObjectInitializer& ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMissionObjective::StaticClass();
}

UObject* UObjectiveFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UMissionObjective* NewObjectAsset = NewObject<UMissionObjective>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

uint32 UObjectiveFactory::GetMenuCategories() const
{
	return FModuleManager::Get().GetModuleChecked<FMissionEditorModule>("MissionEditorModule").AssetCategory;
}

FText UObjectiveFactory::GetDisplayName() const
{
	return LOCTEXT("ObjectiveTest", "Mission Objective");
}

FString UObjectiveFactory::GetDefaultNewAssetName() const
{
	return FString(TEXT("NewMissionObjective"));
}

#undef LOCTEXT_NAMESPACE