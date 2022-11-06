// Copyright (c) 2022 Pocket Sized Animations

#include "ExtendedAIModuleEditor.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"
#include "AIModule.h"

/*editor*/
#include "LevelEditor.h"

/*editor assets (UAssets)*/
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_Base.h"

/*slate*/
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "FExtendedAIModuleEditor"

void FExtendedAIModuleEditor::StartupModule()
{
	/*load asset tools*/
	//IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetCategory =	IAIModule::Get().GetAIAssetCategoryBit();


	/*configure asset registry*/
	//AssetCategory = AssetTools.FindAdvancedAssetCategory(FName(""));
	//AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("ExtendedAIModuleEditor")), LOCTEXT("ExtendedAIModuleCategory", "Extended AI"));
	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_Objective(AssetCategory)));
}

void FExtendedAIModuleEditor::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtendedAIModuleEditor, ExtendedAIModuleEditor);