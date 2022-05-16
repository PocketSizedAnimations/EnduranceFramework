// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InventoryItemComponent.h"
#include "Components/InventoryManagerComponent.h"

// Sets default values for this component's properties
UInventoryItemComponent::UInventoryItemComponent()
{
	/*replication*/
	SetIsReplicatedByDefault(true);
	/*ticking*/
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


// Called when the game starts
void UInventoryItemComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UInventoryItemComponent::OnEquipped()
{

	//OnEquipBegin.Broadcast();
}

void UInventoryItemComponent::OnEquippedFinished()
{
}

void UInventoryItemComponent::BeginEquip()
{

}

void UInventoryItemComponent::EndEquip()
{

}

void UInventoryItemComponent::EnableCollision()
{
	if (GetOwner())
	{
		GetOwner()->SetActorEnableCollision(true);
	}
}

void UInventoryItemComponent::DisableCollision()
{
	if (GetOwner())
	{
		GetOwner()->SetActorEnableCollision(false);
	}
}

void UInventoryItemComponent::EnableVisibility()
{
	if (GetOwner())
	{
		GetOwner()->SetActorHiddenInGame(false);
	}
}

void UInventoryItemComponent::DisableVisibility()
{
	if (GetOwner())
	{
		GetOwner()->SetActorHiddenInGame(true);
	}
}

