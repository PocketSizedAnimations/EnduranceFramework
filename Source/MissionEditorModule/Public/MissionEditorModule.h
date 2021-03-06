// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

class FMissionEditorModule : public IModuleInterface
{
public:

	TSharedPtr<FUICommandList> EditorCommands;

	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;

	void AddToolbarExtension(FToolBarBuilder& Builder);
	
	TSharedRef<SWidget> CreateToolbarButton();

	/*commands*/
	void TestAction();
};
