// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/Guid.h"
#include "QuestUpdate.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DefaultToInstanced)
class QUESTSMODULE_API UQuestUpdate : public UObject
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere)
		FName ID;
	/*quick-internal blerp on what this update does*/
	UPROPERTY(EditAnywhere)
		FName Description;

	/**/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest Updates", meta = (ExposeOnSpawn = true))
		FText NewQuestTitle;
	/*will update Quest description text with the provided one*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest Updates", meta=(ExposeOnSpawn=true))
		FText NewQuestDescription;
	/*if enabled - will combined with existing description as a new line. If false - will replace*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest Updates", meta=(ExposeOnSpawn=true))
		bool bAppendDescription = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Conditions", meta=(ExposeOnSpawn=true))
		bool bRequireQuestItem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Conditions", meta = (MustImplement = "QuestItemInterface", EditCondition = "bRequireQuestItem", ExposeOnSpawn=true))
		TSubclassOf<AActor> QuestItem;
	
};
