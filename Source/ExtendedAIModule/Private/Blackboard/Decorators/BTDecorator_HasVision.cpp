// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_HasVision.h"
#include "Controllers/ExtendedAIController.h"
#include "Components/SensesComponent.h"

UBTDecorator_HasVision::UBTDecorator_HasVision(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NodeName = "Has Vision";
	
}

bool UBTDecorator_HasVision::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AExtendedAIController* AIController = Cast<AExtendedAIController>(OwnerComp.GetAIOwner());

	if (!AIController || !AIController->GetPawn())
		return false;

	/*find SensesComponent*/
	if(USensesComponent* SensesComponent = Cast<USensesComponent>(AIController->GetPawn()->GetComponentByClass(USensesComponent::StaticClass())))
	{
		if (SensesComponent->bHasVision)
			return true;
		else
			return false;
	}

	return false;
}
