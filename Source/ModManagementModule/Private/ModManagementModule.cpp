// Copyright (c) 2022 Pocket Sized Animations

#include "ModManagementModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FModManagementModule"

void FModManagementModule::StartupModule()
{
}

void FModManagementModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModManagementModule, ModManagementModule);