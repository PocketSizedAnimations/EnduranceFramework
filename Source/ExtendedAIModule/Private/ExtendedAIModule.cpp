// Copyright (c) 2022 Pocket Sized Animations

#include "ExtendedAIModule.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FExtendedAIModule"

void FExtendedAIModule::StartupModule()
{
	/*TSharedRef<FSlateStyleSet> StyleSet = MakeShareable(new FSlateStyleSet("MyStyleSet"));

	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	StyleSet->Set("ClassIcon.MyActor", new FSlateImageBrush("path/to/MyActor16.png", FVector2D(16.0f, 16.0f)));
	StyleSet->Set("ClassThumbnail.MyActor", new FSlateImageBrush("path/to/MyActor64.png", FVector2D(64.0f, 64.0f)));

	StyleSet->Set("ClassIcon.MyComponent", new FSlateImageBrush("path/to/MyComponent16.png", FVector2D(16.0f, 16.0f)));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	FClassIconFinder::RegisterIconSource(StyleSet.Get());*/
}

void FExtendedAIModule::ShutdownModule()
{


	//FClassIconFinder::UnregisterIconSource(StyleSet.Get());
	//FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	//ensure(StyleSet.IsUnique());
	//StyleSet.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExtendedAIModule, ExtendedAIModule);