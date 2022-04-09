// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "DeathEvents/DeathEvent.h"
#include "DeathEvent_DisablePlayerInput.generated.h"

/**
 * 
 */
UCLASS(DisplayName="Disable Player Input")
class HEALTHANDSTAMINAMODULE_API UDeathEvent_DisablePlayerInput : public UDeathEvent
{
	GENERATED_BODY()
public:



	virtual void OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator) override;
	
};
