// Copyright (c) 2022 Pocket Sized Animations


#include "Editors/MissionEditor.h"
#include "MissionModule/Public/Objectives/Objective.h"
#include "Internationalization/Text.h"

/*slate*/
#include "GraphEditor.h"



#define LOCTEXT_NAMESPACE "MissionEditor"

const FName FMissionEditor::GraphCanvasTabID(TEXT("MissionEditor_GraphCanvas"));


TSharedRef<SDockTab> FMissionEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == GraphCanvasTabID);
	return SNew(SDockTab)
		.Label(LOCTEXT("MissionGraphCanvasTiele", "Viewport"))
		[
			GraphEditorView.ToSharedRef()
		];
}

FMissionEditor::FMissionEditor()
{

}

FMissionEditor::~FMissionEditor()
{
}

void FMissionEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("MissionEditor", "Mission Editor"));
	
	
	DocumentManager->SetTabManager(InTabManager);
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
	InTabManager->RegisterTabSpawner(GraphCanvasTabID, FOnSpawnTab::CreateSP(this, &Self::SpawnTab_GraphCanvas))
		.SetDisplayName(LOCTEXT("GraphCanvasTab", "Viewport"));
}

void FMissionEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	//Super::InitEditor(Mode, InitToolkitHost, InObject);
	GraphEditorView = CreateGraphWidget();
}

TSharedRef<SGraphEditor> FMissionEditor::CreateGraphWidget()
{
	check(CurrObjectiveEdit);
	// Customize the appearance of the graph.
	FGraphAppearanceInfo AppearanceInfo;
	// The text that appears on the bottom right corner in the graph view.
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_MissionEditor", "Mission");
	AppearanceInfo.InstructionText = LOCTEXT("AppearanceInstructionText_MissionEditor", "Right Click to add new nodes.");

	// Bind graph events actions from the editor
	SGraphEditor::FGraphEditorEvents InEvents;
	//InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FDialogueEditor::OnNodeTitleCommitted);
	//InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FDialogueEditor::OnSelectedNodesChanged);
	//InEvents.OnCreateActionMenu = SGraphEditor::FOnCreateActionMenu::CreateSP(this, &FDialogueEditor::OnCreateGraphActionMenu);

	return SNew(SGraphEditor)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphEvents(InEvents)
		.ShowGraphStateOverlay(false);
	//.AdditionalCommands(GraphEditorCommands)
	//		.GraphToEdit(CurrObjectiveEdit->GetGraph())

}

FLinearColor FMissionEditor::GetWorldCentricTabColorScale() const
{	
	return FLinearColor(0,255,0,1.0);
}

FName FMissionEditor::GetToolkitFName() const
{
	return FName("Mission Editor");
}

FText FMissionEditor::GetBaseToolkitName() const
{
	return FText::FromString("MissionEditor");
}

FString FMissionEditor::GetWorldCentricTabPrefix() const
{
	return FString("MissionEditor");
}

#undef LOCTEXT_NAMESPACE