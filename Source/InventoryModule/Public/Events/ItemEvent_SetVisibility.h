// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Events/ItemEvent.h"
#include "ItemEvent_SetVisibility.generated.h"


UENUM()
enum class EVisibilityInternal : uint8
{
	Visible = 0,
	Hidden = 1
};

/**
 * 
 */
UCLASS(DisplayName = "Set Visibility")
class INVENTORYMODULE_API UItemEvent_SetVisibility : public UItemEvent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category=ItemEvent)
		EVisibilityInternal Visibility;


	virtual void OnItemEventActivated_Implementation(AActor* Item, AActor* User, UInventoryManagerComponent* InventoryManager) override;
};
