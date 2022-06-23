// Copyright (c) 2022 Pocket Sized Animations


#include "Events/ItemEvent_AttachToMesh.h"
#include "Logging.h"
#include "Logging/LogMacros.h"


void UItemEvent_AttachToMesh::OnItemEventActivated_Implementation(AActor* Item, AActor* User, UInventoryManagerComponent* InventoryManager)
{
	Super::OnItemEventActivated_Implementation(Item, User, InventoryManager);

	/*safety check*/
	if (!User)
		return;

	/*class verification*/
	if (ClassExpected != NULL && (User->IsA(ClassExpected.Get()) == false))
		return;
	
	TArray<UObject*> Objects;
	User->GetDefaultSubobjects(Objects);
	for (auto Obj : Objects)
	{
		UE_LOG(LogInventoryModule,Warning,TEXT("%s"),*Obj->GetName());
	}

	if (USceneComponent* Component = Cast<USceneComponent>(User->GetDefaultSubobjectByName(MeshComponentName)))
	{
		FAttachmentTransformRules _AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

		if (AttachmentRule == EAttachmentRule::KeepRelative)
			_AttachmentRules = FAttachmentTransformRules::KeepRelativeTransform;
		else if (AttachmentRule == EAttachmentRule::KeepWorld)
			_AttachmentRules = FAttachmentTransformRules::KeepWorldTransform;
	

		Item->AttachToComponent(Component, _AttachmentRules, SocketName);
		Item->SetActorRelativeTransform(AttachmentOffset);
	}
	else
	{		
		UE_LOG(LogInventoryModule, Warning, TEXT("!!!%s - Event (Attach To Mesh) did not find mesh %s!!!"), *GetNameSafe(Item), *MeshComponentName.ToString());
	}
}
