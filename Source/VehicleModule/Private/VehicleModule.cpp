// Copyright (c) 2022 Pocket Sized Animations

#include "VehicleModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FVehicleModule"

void FVehicleModule::StartupModule()
{
}

void FVehicleModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVehicleModule, VehicleModule);