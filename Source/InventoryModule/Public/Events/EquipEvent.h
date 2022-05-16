// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipEvent.generated.h"

/**
 * 
 */
UCLASS(abstract, EditInlineNew, Blueprintable, AutoExpandCategories=(EquipEvent))
class INVENTORYMODULE_API UEquipEvent : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Equip Event")
		bool bEnabled = true;
};
