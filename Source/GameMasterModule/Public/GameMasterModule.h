// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


#define USES_INVENTORY_MODULE 1

class FGameMasterModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;
	
};
