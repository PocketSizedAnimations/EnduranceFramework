// Copyright (c) 2022 Pocket Sized Animations


#include "DeathEvents/DeathEvent_Delay.h"
#include "TimerManager.h"

void UDeathEvent_Delay::OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator)
{
	Super::OnDeathEventActivated_Implementation(HealthComponent, KilledActor, DeathGiver, DeathInstigator);

	/*safety check*/
	if (KilledActor == nullptr)
		return;

	FTimerHandle TimerHandle;
	KilledActor->GetWorldTimerManager().SetTimer(TimerHandle, this, &UDeathEvent_Delay::OnDelayComplete, Delay, false);	
}

void UDeathEvent_Delay::OnDelayComplete_Implementation()
{

}


