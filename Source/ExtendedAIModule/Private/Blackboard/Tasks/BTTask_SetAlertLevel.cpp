// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Tasks/BTTask_SetAlertLevel.h"
#include "Controllers/ExtendedAIController.h"
#include "Components/SensesComponent.h"

UBTTask_SetAlertLevel::UBTTask_SetAlertLevel()
{
	AlertState = EAlertState::Medium;
	NodeName = "Set Alertness to Medium";
}

void UBTTask_SetAlertLevel::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTTask_SetAlertLevel, AlertState))
	{		
		if (AlertState == EAlertState::Disabled)
			NodeName = "Disable Alert State";
		else if (AlertState == EAlertState::Low)
			NodeName = "Set Alert State to Low";
		else if (AlertState == EAlertState::Medium)
			NodeName = "Set Alert State to Medium";
		else if (AlertState == EAlertState::High)
			NodeName = "Set Alert State to High";
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

EBTNodeResult::Type UBTTask_SetAlertLevel::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	USensesComponent* SensesComponent = Cast<USensesComponent>(AIController->GetPawn()->GetComponentByClass(USensesComponent::StaticClass()));
	
	if (AIController != nullptr && SensesComponent != nullptr)
	{
		if (SensesComponent->GetAlertState() == AlertState)
			return EBTNodeResult::Succeeded;
		else
		{
			SensesComponent->SetAlertState(AlertState);
			return EBTNodeResult::Succeeded;
		}		
	}

	return EBTNodeResult::Failed;
}
