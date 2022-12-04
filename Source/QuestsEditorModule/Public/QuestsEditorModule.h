// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FQuestsEditorModule : public IModuleInterface
{
public:

	uint32 AssetCategory;


	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;
	
};
