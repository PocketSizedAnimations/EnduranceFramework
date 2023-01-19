// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetAggression.generated.h"

UENUM()
enum class ESetAggressionType : uint8
{
	Set,
	Increase,
	Decrease
};


/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTTask_SetAggression : public UBTTaskNode
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, Category = "Aggression")
		ESetAggressionType AggressionModifier = ESetAggressionType::Increase;
	UPROPERTY(EditAnywhere, Category = "Aggression", meta = (UIMin = 0, UIMax = 100, Delta = 5))
		float AggressionLevel = 50.0f;



	UBTTask_SetAggression();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
