// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HasDetectedActors.generated.h"

/**
 * Checks the Owning Actor's SensesCompoment to determine if it has detected any actor
 * can check generically, or specifically and filter by classtype
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_HasDetectedActors : public UBTDecorator
{
	GENERATED_BODY()
public:

	bool bLastValue;

	/*if enabled - performs generic check to check if this actor has detected anything*/
	UPROPERTY(EditAnywhere, Category = "Detection", meta=(ToolTips="If enabled - performs a generic check to see if this actor is aware of ANYTHING"))
		bool bAnyActor = true;
	/*which blackboard key to check if bAnyActor is false*/
	UPROPERTY(EditAnywhere, Category = "Detection",meta = (EditCondition = "!bAnyActor", ToolTips="BlackboardKey entry to check if bAnyActor is disabled"))
		struct FBlackboardKeySelector ActorToCheck;
	/*class filter - filters results to specific class/children of class*/
	UPROPERTY(EditANywhere, Category = "Detection")
		TSubclassOf<AActor> ClassFilter;



	UBTDecorator_HasDetectedActors();
	

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	bool CheckForDetectedActors(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
