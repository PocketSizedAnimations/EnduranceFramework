// Copyright (c) 2022 Pocket Sized Animations


#include "DeathEvents/DeathEvent_DisablePlayerInput.h"


void UDeathEvent_DisablePlayerInput::OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator)
{
	Super::OnDeathEventActivated_Implementation(HealthComponent, KilledActor, DeathGiver, DeathInstigator);

	if (KilledActor == nullptr)
		return;

	if(APawn* P = Cast<APawn>(KilledActor))		
	{
		APlayerController* PC = Cast<APlayerController>(P->GetController());
		KilledActor->DisableInput(PC);
	}
}