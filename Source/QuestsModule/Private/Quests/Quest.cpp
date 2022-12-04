// Copyright (c) 2022 Pocket Sized Animations


#include "Quests/Quest.h"
#include "Quests/QuestUpdate.h"

void UQuest::UpdateQuest(UQuestUpdate* QuestUpdate)
{
	if (QuestUpdate->NewQuestTitle.IsEmpty() == false)
		Title = QuestUpdate->NewQuestTitle;
	if (QuestUpdate->NewQuestDescription.IsEmpty() == false)
	{
		if (QuestUpdate->bAppendDescription == true)
		{
			FString StringCombined = Description.ToString();
			FString OriginalText = Description.ToString();
			FString NewText = QuestUpdate->NewQuestDescription.ToString();
			StringCombined.Append(FString("\r\n\r\n"));
			StringCombined.Append(NewText);
			
			Description = FText::FromString(StringCombined);
		}
			
		else
			Description = QuestUpdate->NewQuestDescription;
	}
}

UQuestUpdate* UQuest::GetQuestUpdateByID(FName ID)
{
	for (auto Update : QuestUpdates)
	{
		if (Update->ID == ID)
			return Update;
	}

	return nullptr;
}