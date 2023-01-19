// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Goal.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_Goal : public UBTDecorator
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Goal")
		TSubclassOf<class UAIGoal> Goal;


	UBTDecorator_Goal();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


	
};
