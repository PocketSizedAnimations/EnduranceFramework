// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_TargetNewEnemy.generated.h"

/** TargetNewEnemy - Updates the CurrentEnemy of the BehaviorComponent for the AI based on configuration
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTService_TargetNewEnemy : public UBTService
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, Category = "Target Conditions")
		bool bTargetHighestThreat = true;
	/*if the AI already has an enemy targeted and a threat with a higher score is founded - that threat must exceed this % compared to the current target in order to switch
	(helps prevent switching back and forth between two similarly scored targets) */
	UPROPERTY(EditAnywhere, Category = "Target Conditions", meta = (UIMin=0.0,UIMax=1.0,ClampMin=0,ClampMax=1.0))
		float TargetSwitchScoreThreshold = 0.075f;


	/*if our AI has switched to a new Target recently - how long (in seconds) until it can switch again (unless Target is killed)*/
	UPROPERTY(EditAnywhere, Category = "Target Switching")
		float TargetSwitchCooldown = 12.0f;

	UBTService_TargetNewEnemy();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	
};
