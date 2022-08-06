// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_HasDetectedActors.h"
#include "Controllers/ExtendedAIController.h"
#include "Components/SensesComponent.h"

UBTDecorator_HasDetectedActors::UBTDecorator_HasDetectedActors()
{
	NodeName = "Has Detected Any Actors";
}

bool UBTDecorator_HasDetectedActors::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AExtendedAIController* AIController = Cast<AExtendedAIController>(OwnerComp.GetAIOwner());

	if (!AIController || !AIController->GetPawn())
		return false;

	/*find SensesComponent*/
	if (USensesComponent* SensesComponent = Cast<USensesComponent>(AIController->GetPawn()->GetComponentByClass(USensesComponent::StaticClass())))
	{
		return SensesComponent->HasDetectedAnyActors();
	}

	return false;
}
