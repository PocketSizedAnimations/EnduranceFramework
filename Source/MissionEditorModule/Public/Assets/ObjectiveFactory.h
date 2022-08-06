// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ObjectiveFactory.generated.h"

/**
 * 
 */
UCLASS()
class MISSIONEDITORMODULE_API UObjectiveFactory : public UFactory
{
	GENERATED_BODY()
public:

	UObjectiveFactory(const FObjectInitializer& ObjectInitializer);
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface

	virtual uint32 GetMenuCategories() const override;
	virtual FText GetDisplayName() const override;
	virtual FString GetDefaultNewAssetName() const override;
};
