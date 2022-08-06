// Copyright (c) 2022 Pocket Sized Animations


#include "Components/StimuliComponent.h"
#include "GameFramework/GameModeBase.h"

UStimuliComponent::UStimuliComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}


void UStimuliComponent::BeginPlay()
{
	Super::BeginPlay();
	
	/*server-initiation*/
	if (GetOwner() && GetNetMode() < NM_Client)
	{
		
		if (GetAISubsystem())
			GetAISubsystem()->RegisterStimuliComponent(this);

	}	
}


void UStimuliComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UStimuliComponent::ProvidesVisualStimuli()
{
	if(bVisualStimuli == false)
		return false;

	return true;
}

