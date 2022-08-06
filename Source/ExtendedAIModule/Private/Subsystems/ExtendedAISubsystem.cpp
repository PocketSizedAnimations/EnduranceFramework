// Copyright (c) 2022 Pocket Sized Animations


#include "Subsystems/ExtendedAISubsystem.h"
#include "Components/SensesComponent.h"
#include "Components/StimuliComponent.h"


void UExtendedAISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UExtendedAISubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UExtendedAISubsystem::RegisterPawn(APawn* NewPawn)
{
	Pawns.AddUnique(NewPawn);
}

void UExtendedAISubsystem::RegisterSensesComponent(USensesComponent* NewSensesComponent)
{
	SensesComponents.AddUnique(NewSensesComponent);
}

void UExtendedAISubsystem::RegisterStimuliComponent(UStimuliComponent* NewStimuliComponent)
{
	StimuliComponents.AddUnique(NewStimuliComponent);
}





TArray<class APawn*> UExtendedAISubsystem::GetAllAIPawns()
{
	return Pawns;
}


TArray<class UStimuliComponent*> UExtendedAISubsystem::GetAllVisualStimuliComponents()
{
	/*initialize list*/
	TArray<UStimuliComponent*> VisualStimuliComponents = TArray<UStimuliComponent*>();

	for (auto Stimuli : StimuliComponents)
	{
		if (Stimuli->ProvidesVisualStimuli())
			VisualStimuliComponents.Add(Stimuli);
	}

	return VisualStimuliComponents;
}

