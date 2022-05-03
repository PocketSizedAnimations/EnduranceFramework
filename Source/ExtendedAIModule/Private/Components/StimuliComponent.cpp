// Copyright (c) 2022 Pocket Sized Animations


#include "Components/StimuliComponent.h"
#include "GameFramework/GameModeBase.h"
#include "AIManagerComponent.h"

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
		UAIManagerComponent* AIManager = Cast<UAIManagerComponent>(GetWorld()->GetAuthGameMode()->GetComponentByClass(UAIManagerComponent::StaticClass()));
		if (AIManager)
		{
			AIManager->RegisterStimuliComponent(this);
		}
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

