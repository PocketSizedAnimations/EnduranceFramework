// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AggressionLevel.generated.h"

UENUM()
enum class EAggressionLevelComparison : uint8
{
	LessThanOrEqualTo,
	GreaterThanOrEqualTo
};

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_AggressionLevel : public UBTDecorator
{
	GENERATED_BODY()
public:
		
	UPROPERTY(EditAnywhere, Category = "Aggression Level")
		EAggressionLevelComparison Comparison = EAggressionLevelComparison::GreaterThanOrEqualTo;
		UPROPERTY(EditAnywhere, Category = "Aggression Level", meta=(UIMin=0,UIMax=100, Delta=5))
			float AggressionLevel = 70.0f;
		
		class AExtendedAIController* AIController;
		class UAIBehaviorCompoment* BehaviorComponent;
		bool LastValue = false;		

		UBTDecorator_AggressionLevel();

		virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
		
		bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
		float GetAggressionLevel() const;
};
