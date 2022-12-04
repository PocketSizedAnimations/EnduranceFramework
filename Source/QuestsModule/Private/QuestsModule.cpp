// Copyright (c) 2022 Pocket Sized Animations

#include "QuestsModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FQuestsModule"

void FQuestsModule::StartupModule()
{
}

void FQuestsModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestsModule, QuestsModule);