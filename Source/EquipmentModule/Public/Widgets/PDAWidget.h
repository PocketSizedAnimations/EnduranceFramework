// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PDAWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoot);

/**
 * 
 */
UCLASS()
class EQUIPMENTMODULE_API UPDAWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
		FOnBoot OnBootBegin;
	UPROPERTY(BlueprintAssignable)
		FOnBoot OnBootComplete;
	UPROPERTY(BlueprintReadOnly, Category = "Test")
		bool bPoweredOn;
	
};
