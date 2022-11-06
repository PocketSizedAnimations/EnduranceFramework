// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ThreatEvaluation.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UThreatEvaluation : public UDataAsset
{
	friend class BTService_EvaluateThreats;

	GENERATED_BODY()
public:
	UPROPERTY()
		class AActor* Actor;
	UPROPERTY()
		class AActor* Owner;

	UPROPERTY()
		float VisibilityScore;
	UPROPERTY()
		float DistanceScore;
	UPROPERTY()
		float ClosestEnemyScore;
	UPROPERTY()
		float FurthestEnemyScore;
	




	//=======================================================================================================================================================
	//=======================================================================FUNCTIONS=======================================================================
	//=======================================================================================================================================================
		

public:
	/*returns the total threat level by adding up all the individual threat scores (which is updated via a BTService_EvaluateThreats (Blackboard Service)*/
	UFUNCTION(BlueprintPure)
		float GetThreatLevel();	

	UFUNCTION()
		void CalcDistanceScore(float MaxDistance, float DistanceScoring);
};
