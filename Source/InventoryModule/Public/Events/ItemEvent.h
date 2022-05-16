// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemEvent.generated.h"

/**
 * 
 */
UCLASS(abstract, EditInlineNew, Blueprintable, AutoExpandCategories = (ItemEvent))
class INVENTORYMODULE_API UItemEvent : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category=ItemEvent)
		bool bEnabled = true;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnItemEventActivated(AActor* Item, AActor* User, class UInventoryManagerComponent* InventoryManager);
};
