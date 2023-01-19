// Copyright (c) 2022 Pocket Sized Animations


#include "Components/QuestManagerComponent.h"
#include "Quests/Quest.h"
#include "UI/QuestJournalWidget.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Quests/Quest.h"

// Sets default values for this component's properties
UQuestManagerComponent::UQuestManagerComponent()
{

	/*replication*/
	SetIsReplicatedByDefault(true);

	/*disable tick - event based*/
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UQuestManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	/*generate the Widget Class*/
	if(QuestJournalWidgetClass && GetOwner()->HasAuthority())
		InitJournalWidget();
}

UQuest* UQuestManagerComponent::AddQuest(UQuest* Quest)
{
	/*safety check*/
	if (Quest == nullptr)
		return nullptr;

	/*check to see if we already have the quest - and return that instead of creating a new one*/
	if (UQuest* existingQuest = GetQuest(Quest))
		return existingQuest;
	
	/*create a new quest instance to be manipulated*/
	UQuest* NewQuest = NewObject<UQuest>(this, Quest->StaticClass(),FName("Quest"), RF_NoFlags, Quest);

	/*add it to our quests*/
	int32 i = Quests.Add(NewQuest);

	/*notify any one listening*/
	if (OnQuestAdded.IsBound())
		OnQuestAdded.Broadcast(this, NewQuest);

	/*notify UI widget of newly added quest*/
	NotifyWidgetOfNewQuest(NewQuest);

	/*return quest*/
	return Quests[i];
}

bool UQuestManagerComponent::RemoveQuest(UQuest* Quest)
{
	/*safety check*/
	if (Quest == nullptr)
		return false;

	for (int32 i = 0; i < Quests.Num(); i++)
	{
		if (Quests[i] && Quests[i]->StaticClass() == Quest->StaticClass())
		{
			Quests.RemoveAt(i);

			if (OnQuestRemoved.IsBound())
				OnQuestRemoved.Broadcast(this, Quest);

			NotifyWidgetOfRemovedQuest(Quest);

			return true;
		}
	}

	return false;
}

UQuest* UQuestManagerComponent::GetQuest(UQuest* Quest)
{
	for (auto QuestItr : Quests)
	{
		if (QuestItr->StaticClass() == Quest->StaticClass())
			return QuestItr;
	}

	return nullptr;
}

bool UQuestManagerComponent::HasQuest(UQuest* Quest, UQuest*& QuestOut)
{
	if (Quest == nullptr)
		return false;


	/*scan through all quests and find matching one if exists*/
	for (auto QuestItr : Quests)
	{
		if (QuestItr->StaticClass() == Quest->StaticClass())
		{
			QuestOut = QuestItr; //assign Quest reference to be used
			return true;
		}
	}

	/*no quest match found*/
	return false;
}

TArray<class UQuest*> UQuestManagerComponent::GetQuests(EQuestStatus StatusFilter)
{
	if (Quests.Num() <= 0)
		return TArray<UQuest*>();

	TArray<UQuest*> QuestResults = TArray<UQuest*>();

	for (auto Quest : Quests)
	{
		if (Quest->Status == StatusFilter)
			QuestResults.Add(Quest);
	}

	return QuestResults;
}


void UQuestManagerComponent::InitJournalWidget()
{
	/*if we're recreating the journal widget - clear out the old one*/
	if (QuestJournalWidget != nullptr)
	{
		QuestJournalWidget->RemoveFromParent();
		QuestJournalWidget->BeginDestroy();
		QuestJournalWidget = nullptr;
	}

	/*create widget*/
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (APlayerController* PC = Cast<APlayerController>(Pawn->GetController()))
		{
			QuestJournalWidget = CreateWidget<UQuestJournalWidget>(PC,QuestJournalWidgetClass,FName("QuestJournalWidget"));
		}
	}
}

void UQuestManagerComponent::OpenJournalWidget()
{
	/*create the journal widget if it does not exist yet*/
	if (QuestJournalWidget == nullptr)
		InitJournalWidget();

	/*open widget*/
	if (QuestJournalWidget)  //safety check
	{
		QuestJournalWidget->AddToViewport();
		QuestJournalWidget->SetFocus();
	}
}

void UQuestManagerComponent::CloseJournalWidget()
{
	if (QuestJournalWidget) //safety check
	{
		QuestJournalWidget->RemoveFromParent();
	}
}

bool UQuestManagerComponent::IsJournalWidgetOpened()
{
	/*return false if the widget hasn't been created yet*/
	if(QuestJournalWidget == nullptr)
		return false;

	return QuestJournalWidget->IsInViewport();
}

void UQuestManagerComponent::NotifyWidgetOfNewQuest(UQuest* Quest)
{
	if (QuestJournalWidget)
		QuestJournalWidget->OnQuestAdded(this, Quest);
}

void UQuestManagerComponent::NotifyWidgetOfRemovedQuest(UQuest* Quest)
{
	if (QuestJournalWidget)
		QuestJournalWidget->OnQuestRemoved(this, Quest);
}

void UQuestManagerComponent::NotifyWidgetOfCompletedQuest(UQuest* Quest)
{
	if (QuestJournalWidget)
		QuestJournalWidget->OnQuestCompleted(this, Quest);
}