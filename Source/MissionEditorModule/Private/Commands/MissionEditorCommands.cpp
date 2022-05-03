// Copyright (c) 2022 Pocket Sized Animations


#include "Commands/MissionEditorCommands.h"
#include "MissionEditorModule.h"

#define LOCTEXT_NAMESPACE "MissionEditorModule"

void FMissionEditorCommands::RegisterCommands()
{
	UI_COMMAND(TestCommand, "TestCommand", "This is a test command", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE

