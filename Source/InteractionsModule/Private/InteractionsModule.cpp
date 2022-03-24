// Copyright (c) 2022 Pocket Sized Animations

#include "InteractionsModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FInteractionsModule"

void FInteractionsModule::StartupModule()
{
}

void FInteractionsModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInteractionsModule, InteractionsModule);