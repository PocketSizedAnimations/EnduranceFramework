// Copyright (c) 2022 Pocket Sized Animations


#include "DeathEvents/DeathEvent_SendToSpectator.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpectatorPawn.h"

void UDeathEvent_SendToSpectator::OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator)
{
	Super::OnDeathEventActivated_Implementation(HealthComponent, KilledActor, DeathGiver, DeathInstigator);
	
	/*safety checks*/
	if (!SpectatorPawnClass || KilledActor == nullptr)
		return;

	if (APawn* P = Cast<APawn>(KilledActor))
	{	
		if (AController* C = P->GetController())
		{
			/*not a player - cancel out*/
			if (C->IsPlayerController() == false)
				return;

			//stop pawn movement
			P->GetMovementComponent()->StopActiveMovement();
			P->GetMovementComponent()->StopMovementImmediately();
			
			// create spectator
			if (C->GetNetMode() < NM_Client) //server-only
			{
				//possess the pawn
				ASpectatorPawn* Spectator = C->GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorPawnClass);
				C->Possess(Spectator);
			}
		}
	}
}
