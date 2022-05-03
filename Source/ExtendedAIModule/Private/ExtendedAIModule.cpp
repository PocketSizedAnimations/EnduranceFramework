// Copyright (c) 2022 Pocket Sized Animations

#include "ExtendedAIModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FExtendedAIModule"

void FExtendedAIModule::StartupModule()
{
}

void FExtendedAIModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtendedAIModule, ExtendedAIModule);