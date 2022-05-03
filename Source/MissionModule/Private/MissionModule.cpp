// Copyright (c) 2022 Pocket Sized Animations

#include "MissionModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FMissionModule"

void FMissionModule::StartupModule()
{
}

void FMissionModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMissionModule, MissionModule);