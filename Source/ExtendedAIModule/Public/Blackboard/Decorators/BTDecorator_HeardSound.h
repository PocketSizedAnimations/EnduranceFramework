// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_HeardSound.generated.h"

enum class ESoundCategory : uint8;

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_HeardSound : public UBTDecorator
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Sound")
		bool bFilterByCategory;
	UPROPERTY(EditAnywhere, Category = "Sound", meta=(EditCondition="bFilterByCategory"))
		ESoundCategory Category;
	UPROPERTY(EditAnywhere, Category = "Sound")
		bool bFilterByDistance;
	UPROPERTY(EditAnywhere, Category = "Sound", meta = (EditCondition = "bFilterByDistance", UIMin=0,ClampMin=0))
		float MaxDistance = 512.0;

	UBTDecorator_HeardSound();



	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;


	
};
