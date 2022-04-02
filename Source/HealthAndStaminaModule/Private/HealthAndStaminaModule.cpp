// Copyright (c) 2022 Pocket Sized Animations

#include "HealthAndStaminaModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FHealthAndStaminaModule"

void FHealthAndStaminaModule::StartupModule()
{
}

void FHealthAndStaminaModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHealthAndStaminaModule, HealthAndStaminaModule);