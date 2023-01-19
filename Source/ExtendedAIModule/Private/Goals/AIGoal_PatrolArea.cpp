// Copyright (c) 2022 Pocket Sized Animations


#include "Goals/AIGoal_PatrolArea.h"

UAIGoal_PatrolArea::UAIGoal_PatrolArea()
{
	DisplayName = "Patrol Area";
	PatrolKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UAIGoal_PatrolArea, PatrolKey));
}