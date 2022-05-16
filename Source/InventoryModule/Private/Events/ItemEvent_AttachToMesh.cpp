// Copyright (c) 2022 Pocket Sized Animations


#include "Events/ItemEvent_AttachToMesh.h"

void UItemEvent_AttachToMesh::OnItemEventActivated_Implementation(AActor* Item, AActor* User, UInventoryManagerComponent* InventoryManager)
{
	Super::OnItemEventActivated_Implementation(Item, User, InventoryManager);

	/*safety check*/
	if (!User)
		return;

	/*class verification*/
	if (ClassExpected != NULL && (User->IsA(ClassExpected.Get()) == false))
		return;

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
}
