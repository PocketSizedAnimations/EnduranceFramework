// Copyright (c) 2022 Pocket Sized Animations


#include "Actors/PDA.h"
#include "Components/WidgetComponent.h"

APDA::APDA(const FObjectInitializer& ObjectInitializer)
{
	
	
	
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("MeshComp"));
	SetRootComponent(Mesh);

	UI = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("UIComp"));
	if (UI)
	{
		UI->SetupAttachment(Mesh);
	}
}
