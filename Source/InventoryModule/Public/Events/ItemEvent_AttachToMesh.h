// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Events/ItemEvent.h"
#include "ItemEvent_AttachToMesh.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Attach to Mesh")
class INVENTORYMODULE_API UItemEvent_AttachToMesh : public UItemEvent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = ItemEvent, meta = (DisplayName="If : Class Is A"))
		TSubclassOf<class AActor> ClassExpected;
	UPROPERTY(EditAnywhere, Category = ItemEvent)
		FName MeshComponentName = "Mesh";
	UPROPERTY(VisibleAnywhere, Category = ItemEvent)
		EAttachmentRule AttachmentRule = EAttachmentRule::SnapToTarget;
	UPROPERTY(EditAnywhere, Category = ItemEvent)
		FName SocketName = "";

	UPROPERTY(EditAnywhere, Category = ItemEvent)
		FTransform AttachmentOffset;


	virtual void OnItemEventActivated_Implementation(AActor* Item, AActor* User, UInventoryManagerComponent* InventoryManager) override;

};
