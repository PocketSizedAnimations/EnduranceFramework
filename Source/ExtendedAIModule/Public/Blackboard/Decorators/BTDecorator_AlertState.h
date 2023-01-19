// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AlertState.generated.h"

/*forward-declaration of EAlertState*/
enum class EAlertState : uint8;

UENUM(BlueprintType)
enum class EAlertStateComparison : uint8
{
	LessThan,
	EqualTo,
	GreaterThan
};


/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_AlertState : public UBTDecorator
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, Category = "Alertness")
		EAlertStateComparison StateComparison;
	UPROPERTY(EditAnywhere, Category = "Alertness")
		EAlertState AlertState;

	class AExtendedAIController* AIController;
	class USensesComponent* SensesComponent;
	bool bLastValue = false;



	UBTDecorator_AlertState();
	
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;


	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	bool CheckAlertState(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
