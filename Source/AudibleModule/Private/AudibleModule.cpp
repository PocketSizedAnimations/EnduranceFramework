// Copyright (c) 2022 Pocket Sized Animations

#include "AudibleModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FAudibleModule"

void FAudibleModule::StartupModule()
{
}

void FAudibleModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAudibleModule, AudibleModule);