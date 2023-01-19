// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_AggressionLevel.h"
#include "Controllers/ExtendedAIController.h"
#include "Components/AIBehaviorCompoment.h"

UBTDecorator_AggressionLevel::UBTDecorator_AggressionLevel()
{	
	FlowAbortMode = EBTFlowAbortMode::Both;
	bNotifyTick = true;
	bCreateNodeInstance = false;
	bNotifyBecomeRelevant = true;
	NodeName = "Aggression >= 75.0%";
}


void UBTDecorator_AggressionLevel::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTDecorator_AggressionLevel, AggressionLevel) || PropertyName == GET_MEMBER_NAME_CHECKED(UBTDecorator_AggressionLevel, Comparison))
	{	
		FString AggressLevelString = FString::SanitizeFloat(AggressionLevel);
		
		if (Comparison == EAggressionLevelComparison::LessThanOrEqualTo)
			NodeName = "Aggression <= " + AggressLevelString;
		else
			NodeName = "Aggression >= " + AggressLevelString;		
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UBTDecorator_AggressionLevel::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AIController == nullptr || BehaviorComponent == nullptr || OwnerComp.GetAIOwner() != AIController)
	{
		AIController = Cast<AExtendedAIController>(OwnerComp.GetAIOwner());
		BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass()));
	}

	bool NewValue = CalculateRawConditionValue(OwnerComp, NodeMemory);

	if (LastValue != NewValue)
	{
		LastValue = NewValue;
		OwnerComp.RequestExecution(this);
	}
}


bool UBTDecorator_AggressionLevel::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	float CurrAggression = GetAggressionLevel();

	//UE_LOG(LogTemp, Log, TEXT("CalcRawCondition::Aggro : %f"), CurrAggression);

	if (CurrAggression <= 0.0f) //uninitialized
		return false;

	if (Comparison == EAggressionLevelComparison::LessThanOrEqualTo)
	{
		//UE_LOG(LogTemp, Log, TEXT("Less Than Condition: %f <= %f"), CurrAggression, AggressionLevel);
		
		if (CurrAggression <= AggressionLevel)
			return true;
		else
			return false;
	}
		
	else if (Comparison == EAggressionLevelComparison::GreaterThanOrEqualTo)
	{
		
		//UE_LOG(LogTemp, Log, TEXT("Greater Than Condition: %f >= %f"), CurrAggression, AggressionLevel);
		
		if (CurrAggression >= AggressionLevel)
			return true;
		else
			return false;
	}

	return false;
}

float UBTDecorator_AggressionLevel::GetAggressionLevel() const
{	
	if(BehaviorComponent)
	{
		return BehaviorComponent->GetAggressionLevel();
	}

	return -1.0f;;
}
