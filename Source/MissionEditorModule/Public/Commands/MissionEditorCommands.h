// Copyright (c) 2022 Pocket Sized Animations

#pragma once
#include "SlateBasics.h"
#include "EditorStyleSet.h"


/**
 * 
 */
class MISSIONEDITORMODULE_API FMissionEditorCommands : public TCommands<FMissionEditorCommands>
{
public:

	TSharedPtr<FUICommandInfo> TestCommand;


	//FMissionEditorCommands()
	//: TCommands<FMissionEditorCommands>(TEXT("MissionEditor"), NSLOCTEXT("Contexts", "MissionEditor", "MissionEditor"), NAME_None, FEditorStyle:GetStyleSetName()) {}
	FMissionEditorCommands()
		: TCommands<FMissionEditorCommands>
		(
			TEXT("TutorialPluginEditor"),
			NSLOCTEXT("Contexts", "TutorialPluginEditor", "TutorialPluginEditor Plugin"),
			NAME_None,
			FEditorStyle::GetStyleSetName()
			) {}
	virtual void RegisterCommands() override;
};
