// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Services/BTService_TargetNewEnemy.h"

UBTService_TargetNewEnemy::UBTService_TargetNewEnemy()
{
	NodeName = "Auto-Target New Enemy";
	bNotifyTick = true;
}

void UBTService_TargetNewEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


}

