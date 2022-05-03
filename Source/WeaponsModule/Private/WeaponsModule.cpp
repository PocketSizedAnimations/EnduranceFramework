// Copyright (c) 2022 Pocket Sized Animations

#include "WeaponsModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FWeaponsModule"

void FWeaponsModule::StartupModule()
{
}

void FWeaponsModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeaponsModule, WeaponsModule);