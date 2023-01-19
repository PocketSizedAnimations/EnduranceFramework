// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Quests/Quest.h"
#include "QuestManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestModified, UQuestManagerComponent*, QuestManager, UQuest*, Quest);

UCLASS( ClassGroup=(Quests), meta=(BlueprintSpawnableComponent) )
class QUESTSMODULE_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:

private:
	/*the current quest this manager is tracking*/
	UPROPERTY()
		class UQuest* ActiveQuest;
	/*any open quests still active*/
	UPROPERTY()
		TArray<class UQuest*> Quests;

public:
	UPROPERTY(BlueprintAssignable)
		FOnQuestModified OnQuestAdded;
	UPROPERTY(BlueprintAssignable)
		FOnQuestModified OnQuestRemoved;
	UPROPERTY(BlueprintAssignable)
		FOnQuestModified OnQuestCompleted;


protected:
	/*the class to use when auto-creating the widget*/
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UQuestJournalWidget> QuestJournalWidgetClass;
	/*the UI/UMG widget we pass events to*/
	UPROPERTY()
		class UQuestJournalWidget* QuestJournalWidget;

	
	

	//=============================================================================================================================
	//==========================================================FUNCTIONS==========================================================
	//=============================================================================================================================

public:	
	// Sets default values for this component's properties
	UQuestManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, Category = "Quests")
		class UQuest* AddQuest(class UQuest* Quest);

	UFUNCTION(BlueprintCallable, Category = "Quests")
		bool RemoveQuest(class UQuest* Quest);

	UFUNCTION(BlueprintPure, Category = "Quests")
		class UQuest* GetQuest(class UQuest* Quest);
	UFUNCTION(BlueprintPure, Category = "Quests")
		bool HasQuest(class UQuest* Quest, UQuest*& QuestOut);
	
	

	UFUNCTION(BlueprintCallable, Category = "Quests")
		TArray<class UQuest*> GetQuests(EQuestStatus StatusFilter = EQuestStatus::Active);	


	
	//==================
	//========UI========
	//==================
public:
	UFUNCTION()
		void InitJournalWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
		void OpenJournalWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
		void CloseJournalWidget();
	UFUNCTION(BlueprintPure, Category = "UI")
		bool IsJournalWidgetOpened();

protected:
	UFUNCTION(BlueprintCallable, Category = "UI")
		void NotifyWidgetOfNewQuest(class UQuest* Quest);
	UFUNCTION(BlueprintCallable, Category = "UI")
		void NotifyWidgetOfRemovedQuest(class UQuest* Quest);
	UFUNCTION(BlueprintCallable, Category = "UI")
		void NotifyWidgetOfCompletedQuest(class UQuest* Quest);
};
