// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "DeathEvents/DeathEvent.h"
#include "DeathEvent_Delay.generated.h"

/** NOT IMPLEMENTED YET
 * 
 */
UCLASS(abstract, DisplayName="Delay", AutoExpandCategories=(DeathEvent))
class HEALTHANDSTAMINAMODULE_API UDeathEvent_Delay : public UDeathEvent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Death Event")
		float Delay = 3.0f;
	UPROPERTY()
		bool bRunningDelay = false;


	virtual void OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator) override;
	UFUNCTION(BlueprintNativeEvent)
		void OnDelayComplete();
};
