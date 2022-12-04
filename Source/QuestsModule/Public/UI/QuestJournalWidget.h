// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Quests/Quest.h"
#include "../Components/QuestManagerComponent.h"
#include "QuestJournalWidget.generated.h"



/**
 * 
 */
UCLASS(abstract)
class QUESTSMODULE_API UQuestJournalWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	

	//===========================================================================================================================
	//=========================================================FUNCTIONS=========================================================
	//===========================================================================================================================
	
	UQuestJournalWidget(const FObjectInitializer& ObjectInitializer);

	/*event that'll fire whenever a new quest is added*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Quests")
		void OnQuestAdded(class UQuestManagerComponent* QuestManager, class UQuest* Quest);
	UFUNCTION(BlueprintImplementableEvent, Category = "Quests")
		void OnQuestRemoved(class UQuestManagerComponent* QuestManager, class UQuest* Quest);
	UFUNCTION(BlueprintImplementableEvent, Category = "Quests")
		void OnQuestCompleted(class UQuestManagerComponent* QuestManager, class UQuest* Quest);
};
