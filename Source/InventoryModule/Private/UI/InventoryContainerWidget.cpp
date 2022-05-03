// Copyright (c) 2022 Pocket Sized Animations


#include "UI/InventoryContainerWidget.h"

UInventoryContainerWidget::UInventoryContainerWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bIsFocusable = true;
}

TArray<AActor*> UInventoryContainerWidget::GetInventory()
{
	return TArray<AActor*>();
}
