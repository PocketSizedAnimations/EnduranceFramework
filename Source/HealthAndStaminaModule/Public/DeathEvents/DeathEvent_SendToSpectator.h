// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "DeathEvents/DeathEvent.h"
#include "DeathEvent_SendToSpectator.generated.h"

UENUM()
enum class ESpectatorTransitionType : uint8
{
	Instant,
	LerpToLocation
};

/**
 * 
 */
UCLASS(DisplayName="Send To Spectator")
class HEALTHANDSTAMINAMODULE_API UDeathEvent_SendToSpectator : public UDeathEvent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Death Event", meta=(EditCondition=bEnabled))
		ESpectatorTransitionType TransitionType = ESpectatorTransitionType::Instant;
	UPROPERTY(EditAnywhere, Category = "Death Event", meta = (EditCondition = bEnabled))
		class TSubclassOf<ASpectatorPawn> SpectatorPawnClass;



	virtual void OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator) override;
};
