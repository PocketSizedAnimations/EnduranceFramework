// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FVehicleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	void StartupModule() override;
	void ShutdownModule() override;
	
};
