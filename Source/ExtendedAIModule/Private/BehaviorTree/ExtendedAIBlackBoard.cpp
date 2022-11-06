// Copyright (c) 2022 Pocket Sized Animations


#include "BehaviorTree/ExtendedAIBlackBoard.h"

#include "Editor.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/UObjectHash.h"
#include "UObject/UObjectIterator.h"
#include "AISystem.h"
#include "Async/Async.h"


/*blackboard keys*/
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


void UExtendedAIBlackBoard::PostInitProperties()
{
	Super::PostInitProperties();

	UBlackboardData& Asset = *this;
	// note that UpdatePersistentKey will return non-null only if a given key gets newly created 
	CurrentEnemy = Asset.UpdatePersistentKey<UBlackboardKeyType_Object>(FName("CurrentEnemy"));

	if (CurrentEnemy)
	{
		CurrentEnemy->BaseClass = APawn::StaticClass();
		#if WITH_EDITOR
				// MarkPackageDirty returning false means marking wasn't possible at this moment. Give it one more try in a moment
				if (GEditor != nullptr && Asset.MarkPackageDirty() == false)
				{
					TWeakObjectPtr<UBlackboardData> WeakAsset = &Asset;
					AsyncTask(ENamedThreads::GameThread, [WeakAsset]() {
						if (UBlackboardData* AssetPtr = WeakAsset.Get())
						{
							AssetPtr->MarkPackageDirty();
						}
						});
				}
		#endif // WITH_EDITOR
	}

	
}
