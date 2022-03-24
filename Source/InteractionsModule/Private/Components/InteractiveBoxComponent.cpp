// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InteractiveBoxComponent.h"

UInteractiveBoxComponent::UInteractiveBoxComponent()
{
	
	/*Editor Visualizer*/
	ShapeColor = FColor(55, 195, 251, 255);
	LineThickness = 1.0f;
}

bool UInteractiveBoxComponent::IsInteractive(AActor* User)
{		
	if (bDisableInteraction)
		return false;

	return bIsInteractive;
}

bool UInteractiveBoxComponent::IsInteractionEnabled()
{
	return !bDisableInteraction;
}

/*starts the interaction*/
bool UInteractiveBoxComponent::BeginInteraction(AActor* User)
{	
	/*cancel interaction*/	
	if (!IsInteractive(User))
	{		
		EndInteraction(User, true);
		return false;
	}

	/*notify*/
	if (OnInteractionBegin.IsBound())
		OnInteractionBegin.Broadcast(GetOwner(), User);

	return true;	
}

/*EndInteraction() - Called whenever an interaction is completed, or canceled*/
/*@bInteractionCanceled - considered canceled mid-action if true, otherwise assumes completed successfully*/
void UInteractiveBoxComponent::EndInteraction(AActor* User, bool bInteractionCanceled)
{		
	/*event notifiers*/
	/*Generic Interaction Ended*/
	if (OnInteractionEnd.IsBound())
		OnInteractionEnd.Broadcast(GetOwner(), User);

	if (!bInteractionCanceled && OnInteractionCompleted.IsBound())
		OnInteractionCompleted.Broadcast(GetOwner(), User);

	/*Interaction Canceled*/
	if (bInteractionCanceled && OnInteractionCanceled.IsBound())
		OnInteractionCanceled.Broadcast(GetOwner(), User);		
}

float UInteractiveBoxComponent::GetCurrentInteractionTime()
{
	return 0.0f;
}

float UInteractiveBoxComponent::GetRemainingInteractionTime()
{
	return 0.0f;
}
