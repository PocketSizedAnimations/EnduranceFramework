// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryContainerWidget.generated.h"

/**
 * 
 */
UCLASS(abstract)
class INVENTORYMODULE_API UInventoryContainerWidget : public UUserWidget
{
	friend class UInventoryManagerComponent;

	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadWrite)
		UInventoryManagerComponent* InventoryManager;
	 
	//=================================================================================================================
	//====================================================FUNCTIONS====================================================
	//=================================================================================================================
	UInventoryContainerWidget(const FObjectInitializer& ObjectInitializer);
	

	UFUNCTION(BlueprintPure)
		TArray<AActor*> GetInventory();



};
