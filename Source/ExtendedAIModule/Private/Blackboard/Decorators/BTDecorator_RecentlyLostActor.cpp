// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_RecentlyLostActor.h"

UBTDecorator_RecentlyLostActor::UBTDecorator_RecentlyLostActor()
{
	NodeName = "Recently Lost Actor";
	FlowAbortMode = EBTFlowAbortMode::Both;
	bNotifyTick = true;
	bLastValue = false;
	bCreateNodeInstance = false;
}


