// Copyright (c) 2022 Pocket Sized Animations


#include "Controllers/ExtendedAIController.h"
#include "Subsystems/ExtendedAISubsystem.h"

AExtendedAIController::AExtendedAIController()
{

}

void AExtendedAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AExtendedAIController::OnPossess(APawn* InPawn)
{
	GetAISubsystem()->RegisterPawn(InPawn);

	Super::OnPossess(InPawn);
}




UExtendedAISubsystem* AExtendedAIController::GetAISubsystem()
{
	return GetWorld()->GetSubsystem<UExtendedAISubsystem>();	
}


