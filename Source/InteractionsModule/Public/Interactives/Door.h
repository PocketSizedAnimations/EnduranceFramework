// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"


UCLASS(Blueprintable, HideCategories=(ActorTick,Replication,Rendering,Collision,Actor,Input,HLOD,Cooking))
class INTERACTIONSMODULE_API ADoor : public AActor
{
	GENERATED_BODY()
public:




public:	
	// Sets default values for this actor's properties
	ADoor(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
