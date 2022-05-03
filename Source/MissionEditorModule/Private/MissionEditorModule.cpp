// Copyright (c) 2022 Pocket Sized Animations

#include "MissionEditorModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"
#include "..\Public\MissionEditorModule.h"
#include "Commands/MissionEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"



#define LOCTEXT_NAMESPACE "FMissionEditorModule"

void FMissionEditorModule::StartupModule()
{
	/*construct commands*/
	FMissionEditorCommands::Register();
	EditorCommands = MakeShareable(new FUICommandList);
	EditorCommands->MapAction(FMissionEditorCommands::Get().TestCommand, FExecuteAction::CreateRaw(this, &FMissionEditorModule::TestAction));

	/*construct the toolbar menu*/
	TSharedPtr<FExtender> MissionToolbarExtender = MakeShareable(new FExtender);
	MissionToolbarExtender->AddToolBarExtension("ProjectSettings", EExtensionHook::Before, EditorCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMissionEditorModule::AddToolbarExtension));

	/*add it to the Toolbar Extension Manager - which will be picked up later and injected when the Toolbar is created*/
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor"); //loads the LevelEditorModule
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(MissionToolbarExtender); //push our toolbar into the extension of LevelEditorModule
}

void FMissionEditorModule::ShutdownModule()
{
	
}

void FMissionEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddSeparator();
	Builder.AddToolBarButton(FMissionEditorCommands::Get().TestCommand, "Mission Editor");
	Builder.AddToolBarWidget(CreateToolbarButton());
	Builder.AddSeparator();
}


TSharedRef<SWidget> FMissionEditorModule::CreateToolbarButton()
{
	return
		SNew(SButton)
		.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		.ForegroundColor(FSlateColor::UseForeground())
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString("MissionEditor"))
			//.Text_Static(FString("MissionEditor"))
			.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 8))
			.ColorAndOpacity(FLinearColor(1, 0, 1, 1))

			]
		];
		
		/*SNew(SButton)
		.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.ForegroundColor(FSlateColor::UseForeground())
		[
			SNew(SBorder)
			.Padding(FMargin(3))
		.BorderImage(FCoreStyle::Get().GetBrush("ColorSpectrum.Spectrum"))
		[
			SNew(STextBlock)
			.Text(FString("Mission Editor"))
			.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 16))
			.ColorAndOpacity(FLinearColor(1,0,1,1))
			.HighlightColor(FLinearColor(1,1,0,1))			
				]
		];*/
}

void FMissionEditorModule::TestAction()
{
	UE_LOG(LogTemp, Warning, TEXT("RAWR!"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMissionEditorModule, MissionEditorModule);