// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Goals/AIGoal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EnvironmentQuery/EnvQuery.h"


#include "AIGoal_PatrolArea.generated.h"

UENUM()
enum class EPatrolStartType : uint8
{
	BlackboardKey,
	CurrentLocation
};

UENUM()
enum class EPatrolPattern : uint8
{
	EQSQuery
};
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, DisplayName="Patrol Area")
class EXTENDEDAIMODULE_API UAIGoal_PatrolArea : public UAIGoal
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Goal Configuration")
		EPatrolStartType PatrolStartType;
	UPROPERTY(EditAnywhere, Category = "Goal Configuration")
		EPatrolPattern PatrolPattern;
	UPROPERTY(EditAnywhere, Category = "Goal Configuration", meta=(EditCondition="PatrolStartType == EPatrolStartType::BlackboardKey"))
		struct FBlackboardKeySelector PatrolKey;
	UPROPERTY(EditAnywhere, Category = "Goal Configuration", meta = (EditCondition = "PatrolPattern == EPatrolPattern::EQSQuery"))
		class UEnvQuery* QueryTemplate;



	UAIGoal_PatrolArea();





};
