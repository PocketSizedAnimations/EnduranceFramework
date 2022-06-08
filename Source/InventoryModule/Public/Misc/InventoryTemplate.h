// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryTemplate.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INVENTORYMODULE_API UInventoryTemplate : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (MustImplement = "InventoryItemInterface"))
		TArray<TSubclassOf<class AActor>> Inventory;
	
};
