// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InteractiveBoxComponent.h"
#include "Interfaces/InteractiveActorInterface.h"

/*replication*/
#include "Net/UnrealNetwork.h"

void UInteractiveBoxComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInteractiveBoxComponent, bIsInteractive);
	DOREPLIFETIME(UInteractiveBoxComponent, bInteractionDisabled);
	DOREPLIFETIME(UInteractiveBoxComponent, bInteractionActive);
	DOREPLIFETIME(UInteractiveBoxComponent, CurrentUser);
}

UInteractiveBoxComponent::UInteractiveBoxComponent()
{
	
	/*Editor Visualizer*/
	ShapeColor = FColor(55, 195, 251, 255);
	LineThickness = 1.0f;

	/*repliclation*/
	SetIsReplicatedByDefault(true);
}

bool UInteractiveBoxComponent::IsInteractionAvailable(AActor* User)
{		
	if (bInteractionDisabled)
		return false;

	/*if our owner (actor) is using the InteractiveActorInterface let them override the results*/
	if (GetOwner()->GetClass()->ImplementsInterface(UInteractiveActorInterface::StaticClass()))
		return Cast<IInteractiveActorInterface>(GetOwner())->Execute_IsInteractionAvailable(GetOwner(),User);

	return bIsInteractive;
}

/*whether or not this interactive should be pickedu up by traces currently or not*/
bool UInteractiveBoxComponent::IsInteractionEnabled()
{
	return !bInteractionDisabled;
}

/*starts the interaction*/
bool UInteractiveBoxComponent::BeginInteraction(AActor* User)
{	
	/*cancel interaction*/	
	if (!IsInteractionAvailable(User))
	{		
		CancelInteraction(User);
		return false;
	}

	SetActiveUser(User);
	
	/*if this interaction is meant to be instantly processed (rather than a key-hold) go ahead and do so*/
	if (InteractionType == EInteractionType::Instant)
		CompleteInteraction(User);

	/*notify*/
	if (OnInteractionBegin.IsBound())
		OnInteractionBegin.Broadcast(GetOwner(), User);

	return true;	
}

/*EndInteraction() - Called whenever an interaction key is let go*/
void UInteractiveBoxComponent::EndInteraction(AActor* User)
{	
	RemoveActiveUser(User);

	/*Generic Interaction Ended*/
	if (OnInteractionEnd.IsBound())
		OnInteractionEnd.Broadcast(GetOwner(), User);
}

void UInteractiveBoxComponent::CancelInteraction(AActor* User)
{
	RemoveActiveUser(User);

	/*Interaction Canceled*/
	if (OnInteractionCanceled.IsBound())
		OnInteractionCanceled.Broadcast(GetOwner(), User);
}

void UInteractiveBoxComponent::CompleteInteraction(AActor* User)
{	
	/*interaction completed*/
	if (OnInteractionCompleted.IsBound())
		OnInteractionCompleted.Broadcast(GetOwner(), User);
}


void UInteractiveBoxComponent::OnHoverBegin(AActor* User)
{
	if (bHovered == false)
	{
		bHovered = true;

		if (OnHover.IsBound())
			OnHover.Broadcast(GetOwner(), User);
	}	
}

void UInteractiveBoxComponent::OnHoverEnd(AActor* User)
{
	if (bHovered)
	{
		bHovered = false;

		if (OnUnhover.IsBound())
			OnUnhover.Broadcast(GetOwner(), User);
	}	
}

float UInteractiveBoxComponent::GetCurrentInteractionTime()
{
	return 0.0f;
}

float UInteractiveBoxComponent::GetRemainingInteractionTime()
{
	return 0.0f;
}

void UInteractiveBoxComponent::SetActiveUser(AActor* User)
{
	/*beginning of interaction starts*/
	bInteractionActive = true;
	CurrentUser = User;
}

void UInteractiveBoxComponent::RemoveActiveUser(AActor* User)
{
	if (CurrentUser == User)
	{
		bInteractionActive = false;
		CurrentUser = nullptr;
	}
}
