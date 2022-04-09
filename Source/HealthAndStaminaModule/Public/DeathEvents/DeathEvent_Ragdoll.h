// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "DeathEvents/DeathEvent.h"
#include "DeathEvent_Ragdoll.generated.h"

/**
 * 
 */
UCLASS(DisplayName="Ragdoll",AutoExpandCategories=(DeathEvent))
class HEALTHANDSTAMINAMODULE_API UDeathEvent_Ragdoll : public UDeathEvent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category="Death Event", meta = (EditCondition = bEnabled))
		bool bDisableCapsuleCollision = true;

	virtual void OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator) override;


};
