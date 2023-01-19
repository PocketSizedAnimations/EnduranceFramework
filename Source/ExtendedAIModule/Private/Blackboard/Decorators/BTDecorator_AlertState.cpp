// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_AlertState.h"
#include "Controllers/ExtendedAIController.h"
#include "Components/SensesComponent.h"

UBTDecorator_AlertState::UBTDecorator_AlertState()
{
	StateComparison = EAlertStateComparison::EqualTo;
	AlertState = EAlertState::Medium;
	NodeName = "AlertState is Medium";

	FlowAbortMode = EBTFlowAbortMode::Both;
	bNotifyTick = true;
	bCreateNodeInstance = false;

	bAllowAbortNone = false;
	bAllowAbortLowerPri = false;
	bAllowAbortChildNodes = true;
}



void UBTDecorator_AlertState::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTDecorator_AlertState, StateComparison) || PropertyName == GET_MEMBER_NAME_CHECKED(UBTDecorator_AlertState, AlertState))
	{		
		FString ComparisonString = "is";
		FString StateString = "Medium";
		if (StateComparison == EAlertStateComparison::LessThan)
			ComparisonString = "Less Than";
		else if (StateComparison == EAlertStateComparison::GreaterThan)
			ComparisonString = "Greater Than";

		if (AlertState == EAlertState::Low)
			StateString = "Low";
		else if (AlertState == EAlertState::High)
			StateString = "High";
		else if (AlertState == EAlertState::Disabled)
			StateString = "Disabled";

		NodeName = "AlertState " + ComparisonString + " " + StateString;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UBTDecorator_AlertState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AIController == nullptr || SensesComponent == nullptr || OwnerComp.GetAIOwner() != AIController)
	{
		AIController = Cast<AExtendedAIController>(OwnerComp.GetAIOwner());
		SensesComponent = Cast<USensesComponent>(AIController->GetPawn()->GetComponentByClass(USensesComponent::StaticClass()));
	}

	bool bCurrentValue = CheckAlertState(OwnerComp, NodeMemory);
	if (bLastValue != bCurrentValue)
	{
		bLastValue = bCurrentValue;
		OwnerComp.RequestExecution(this);
	}
}

bool UBTDecorator_AlertState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return CheckAlertState(OwnerComp,NodeMemory);
}

bool UBTDecorator_AlertState::CheckAlertState(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!AIController || !AIController->GetPawn())
		return false;

	if (SensesComponent)
	{
		if (StateComparison == EAlertStateComparison::LessThan)
			return (SensesComponent->GetAlertState() < AlertState);
		else if (StateComparison == EAlertStateComparison::EqualTo)
			return (SensesComponent->GetAlertState() == AlertState);
		else
			return (SensesComponent->GetAlertState() > AlertState);		
	}

	return false;
}
