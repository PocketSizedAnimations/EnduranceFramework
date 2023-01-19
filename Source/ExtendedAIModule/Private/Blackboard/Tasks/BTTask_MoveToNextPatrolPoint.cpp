// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Tasks/BTTask_MoveToNextPatrolPoint.h"
#include "Goals/AIGoal_PatrolArea.h"
#include "Components/AIBehaviorCompoment.h"
#include "BehaviorTree/Tasks/BTTask_RunEQSQuery.h"
#include "AIController.h"


UBTTask_MoveToNextPatrolPoint::UBTTask_MoveToNextPatrolPoint()
{
	NodeName = "Move to Next Patrol Point";
}

EBTNodeResult::Type UBTTask_MoveToNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UAIBehaviorCompoment* BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass()));

	if (AIController && BehaviorComponent)
	{
		UAIGoal_PatrolArea* PatrolGoal = Cast<UAIGoal_PatrolArea>(BehaviorComponent->GetGoal());
		if (PatrolGoal)
		{
			PatrolGoal->QueryTemplate;
		}
	}


	return EBTNodeResult::Failed;
}
