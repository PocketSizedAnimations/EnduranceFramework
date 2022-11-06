// Copyright (c) 2022 Pocket Sized Animations


#include "DataAssets/ThreatEvaluation.h"





float UThreatEvaluation::GetThreatLevel()
{
	return
		VisibilityScore
		+DistanceScore
		+ClosestEnemyScore
		+FurthestEnemyScore		
		;
}

void UThreatEvaluation::CalcDistanceScore(float MaxDistance, float DistanceScoring)
{
	if (Actor == nullptr)
		return;

	//float Distance = 
}

