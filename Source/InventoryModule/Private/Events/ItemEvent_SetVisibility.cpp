// Copyright (c) 2022 Pocket Sized Animations


#include "Events/ItemEvent_SetVisibility.h"

void UItemEvent_SetVisibility::OnItemEventActivated_Implementation(AActor* Item, AActor* User, UInventoryManagerComponent* InventoryManager)
{
	Super::OnItemEventActivated_Implementation(Item, User, InventoryManager);

	if (Visibility == EVisibilityInternal::Visible)
		Item->SetActorHiddenInGame(false);
	else
		Item->SetActorHiddenInGame(true);
}

