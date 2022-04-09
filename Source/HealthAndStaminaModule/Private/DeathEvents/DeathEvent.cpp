// Copyright (c) 2022 Pocket Sized Animations


#include "DeathEvents/DeathEvent.h"
#include "Components/SimpleHealthComponent.h"

void UDeathEvent::OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator)
{
	if (!bEnabled)
		return;

}
