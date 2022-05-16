// Copyright (c) 2022 Pocket Sized Animations


#include "Events/ItemEvent.h"

void UItemEvent::OnItemEventActivated_Implementation(AActor* Item, AActor* User, UInventoryManagerComponent* InventoryManager)
{
	if (!bEnabled)
		return;
}
