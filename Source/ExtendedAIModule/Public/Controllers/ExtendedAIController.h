// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ExtendedAIController.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API AExtendedAIController : public AAIController
{
	GENERATED_BODY()
public:





	//===========================================================================================================================
	//=========================================================FUNCTIONS=========================================================
	//===========================================================================================================================
public:
	//================================
	//=========initialization=========
	//================================
	AExtendedAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;




	//=====================
	//======SUBSYSTEM======
	//=====================
	UFUNCTION()
		class UExtendedAISubsystem* GetAISubsystem();
};
