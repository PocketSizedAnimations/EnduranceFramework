// Copyright (c) 2022 Pocket Sized Animations

#include "ExtendedFirstPersonModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FExtendedFirstPersonModule"

void FExtendedFirstPersonModule::StartupModule()
{
}

void FExtendedFirstPersonModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtendedFirstPersonModule, ExtendedFirstPersonModule);