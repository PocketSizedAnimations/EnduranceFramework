// Copyright (c) 2022 Pocket Sized Animations

#include "GameMasterModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FGameMasterModule"

void FGameMasterModule::StartupModule()
{
}

void FGameMasterModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameMasterModule, GameMasterModule);