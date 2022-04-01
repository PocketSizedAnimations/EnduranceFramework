// Copyright (c) 2022 Pocket Sized Animations


#include "Components/EngineComponent.h"

void UEngineComponent::StartEngine()
{
	bEngineRunning = true;
}

void UEngineComponent::StopEngine()
{
	bEngineRunning = false;
}

bool UEngineComponent::IsEngineRunning()
{
	return bEngineRunning;
}
