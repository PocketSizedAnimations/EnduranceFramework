// Copyright (c) 2022 Pocket Sized Animations

#include "QuestsEditorModule.h"
#include "Logging.h"

#include "Assets/QuestFactory.h"

/*editor*/
#include "LevelEditor.h"

/*editor assets (UAssets)*/
#include "IAssetTools.h"
#include "AssetToolsModule.h"

/*slate*/
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FQuestsEditorModule"

void FQuestsEditorModule::StartupModule()
{
	
	/*add asset-registry*/
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("QuestsEditorModule")), LOCTEXT("QuestsModuleCategory", "Quests"));
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_Quest(AssetCategory)));
}

void FQuestsEditorModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestsEditorModule, QuestsEditorModule);