// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "Engine/DataAsset.h"
#include "AIGoal.generated.h"

UENUM(BlueprintType)
enum class EGoalStatus : uint8
{
	NotStarted,
	InProgress,
	Succeeded,
	Failed
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, abstract)
class EXTENDEDAIMODULE_API UAIGoal : public UObject
{
	GENERATED_BODY()
public:


	UPROPERTY(VisibleAnywhere, Category = "Goal Configuration")
		FString DisplayName = "Goal Name";
	UPROPERTY()
		EGoalStatus GoalStatus = EGoalStatus::NotStarted;


};

