// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "EditorUndoClient.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"


/**
 * 
 */
class MISSIONEDITORMODULE_API FMissionEditor : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
public:

	typedef FMissionEditor Self;
	SLATE_BEGIN_ARGS(Self) {}
	SLATE_END_ARGS()

	/*managers && views*/
	TSharedPtr<FDocumentTracker> DocumentManager;
	TSharedPtr<SGraphEditor> GraphEditorView;
	
	/*tab creation*/
	static const FName GraphCanvasTabID;
	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args) const;

	/*asset modifying*/
	class UMissionObjective* CurrObjectiveEdit;



	FMissionEditor();
	virtual ~FMissionEditor();

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* InObject);

	TSharedRef<SGraphEditor> CreateGraphWidget();

	// Inherited via FWorkflowCentricApplication
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
};
