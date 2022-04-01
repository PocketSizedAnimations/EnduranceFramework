// Copyright (c) 2022 Pocket Sized Animations

#include "EquipmentModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FEquipmentModule"

void FEquipmentModule::StartupModule()
{
}

void FEquipmentModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEquipmentModule, EquipmentModule);