// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_State.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_State : public UBTDecorator
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "State")
		TSubclassOf<class UAIState> State;


	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	UBTDecorator_State();


	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


	
};
