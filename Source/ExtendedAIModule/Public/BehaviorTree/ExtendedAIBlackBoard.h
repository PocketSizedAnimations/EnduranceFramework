// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "ExtendedAIBlackBoard.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UExtendedAIBlackBoard : public UBlackboardData
{
	GENERATED_BODY()
public:




	//=======================================================================================================================
	//=======================================================FUNCTIONS=======================================================
	//=======================================================================================================================

	//====================================
	//===========INITIALIZATION===========
	//====================================
	virtual void PostInitProperties() override;


	
};
