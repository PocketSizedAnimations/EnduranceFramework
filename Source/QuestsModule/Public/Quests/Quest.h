// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Misc/Guid.h"
#include "Quest.generated.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
	Inactive,
	Active,
	Completed
};


/**
 * 
 */
UCLASS(BlueprintType)
class QUESTSMODULE_API UQuest : public UDataAsset
{
	GENERATED_BODY()
public:


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Quest", meta = (ExposedOnSpawn=True))
		FText Title;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Quest", meta=(ExposedOnSpawn=True))
		FText Description;
	UPROPERTY(BlueprintReadOnly, Category = "Quest", meta = (ExposdOnSpawn = True))
		EQuestStatus Status = EQuestStatus::Active;


	UPROPERTY(EditAnywhere, Category = "Quest Updates", Instanced)
		TArray<class UQuestUpdate*> QuestUpdates;

	
	
	//=========================================================================================================================
	//========================================================FUNCTIONS========================================================
	//=========================================================================================================================

	UFUNCTION(BlueprintCallable, Category = "Quest")
		void UpdateQuest(class UQuestUpdate* QuestUpdate);
	/*returns the QuestUpdate object by searching the quest for a matching ID*/
	UFUNCTION(BlueprintPure, Category = "Quest")
		class UQuestUpdate* GetQuestUpdateByID(FName ID);

};
