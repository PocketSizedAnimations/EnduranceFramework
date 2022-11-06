// Copyright (c) 2022 Pocket Sized Animations


#include "Assets/ExtendedBlackboardFactory.h"

#include "ExtendedAIModuleEditor.h"
#include "ExtendedAIModule/Public/BehaviorTree/ExtendedAIBlackBoard.h"

#define LOCTEXT_NAMESPACE "ExtendedAIModuleEditor" 

UExtendedBlackboardFactory::UExtendedBlackboardFactory(const FObjectInitializer& ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UExtendedAIBlackBoard::StaticClass();
}

UObject* UExtendedBlackboardFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UExtendedAIBlackBoard* NewObjectAsset = NewObject<UExtendedAIBlackBoard>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

uint32 UExtendedBlackboardFactory::GetMenuCategories() const
{
	return FModuleManager::Get().GetModuleChecked<FExtendedAIModuleEditor>("ExtendedAIModuleEditor").AssetCategory;
}

FText UExtendedBlackboardFactory::GetDisplayName() const
{
	return LOCTEXT("ExtBlackboard", "Extended AI Blackboard");
}

FString UExtendedBlackboardFactory::GetDefaultNewAssetName() const
{
	return FString(TEXT("NewExtendedBlackboard"));
}

#undef LOCTEXT_NAMESPACE