// Copyright (c) 2022 Pocket Sized Animations

#include "FirstPersonModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FFirstPersonModule"

void FFirstPersonModule::StartupModule()
{
}

void FFirstPersonModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFirstPersonModule, FirstPersonModule);