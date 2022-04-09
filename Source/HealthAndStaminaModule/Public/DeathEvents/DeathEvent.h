// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
//#include "Engine/DataAsset.h"
#include "UObject/NoExportTypes.h"
#include "DeathEvent.generated.h"

/**
 * 
 */
UCLASS(abstract, EditInlineNew, Blueprintable,AutoExpandCategories=(DeathEvent))
class HEALTHANDSTAMINAMODULE_API UDeathEvent : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Death Event")
		bool bEnabled = true;



	/*
	* Called by both Server and Client - be sure to account for networking needs
	@param DeathGiver - this is the OBJECT that killed the KilledActor
	@param DeathInstigator - this is the CONTROLLER responsible for DeathGiver actor (if anyone - could be NULL)
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnDeathEventActivated(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator);
};
