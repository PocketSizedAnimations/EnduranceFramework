// Copyright (c) 2022 Pocket Sized Animations


#include "AIManagerComponent.h"
#include "Components/SensesComponent.h"
#include "Components/StimuliComponent.h"

// Sets default values for this component's properties
UAIManagerComponent::UAIManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIManagerComponent::RegisterSensesComponent(USensesComponent* NewSensesComponent)
{
	SensesComponents.AddUnique(NewSensesComponent);
}

void UAIManagerComponent::RegisterStimuliComponent(UStimuliComponent* NewStimuliComponent)
{
	StimuliComponents.AddUnique(NewStimuliComponent);
}

TArray<class UStimuliComponent*> UAIManagerComponent::GetAllVisualStimuliComponents()
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
