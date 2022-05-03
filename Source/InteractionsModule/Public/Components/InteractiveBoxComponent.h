// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/InteractiveManagerComponent.h"
#include "Interfaces/InteractiveShapeInterface.h"
#include "InteractiveBoxComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Interactions), HideCategories = ("Sockets","Navigation",Rendering,Physics,"Component Tick"), meta = (BlueprintSpawnableComponent))
class INTERACTIONSMODULE_API UInteractiveBoxComponent : public UBoxComponent, public IInteractiveShapeInterface
{
	GENERATED_BODY()
public:
	/*whether or not this object can be interacted with currently - attempting to use an interactive that has this set as false will immedietely cancel the action - still shows up in traces*/
	UPROPERTY(EditAnywhere, Category = "Interactions")
		bool bIsInteractive = true;
	/*when disabled - will be disregarded by a InteractiveManager's trace entirely - preventing it from showing up in the list*/
	UPROPERTY(EditAnywhere, Category = "Interactions")
		bool bDisableInteraction = false;

	
	/*DELEGATES/EVENTS*/

	/*interaction started*/
	UPROPERTY(BlueprintAssignable)
		FOnInteraction OnInteractionBegin;
	/*generic interaction ended (success & failure)*/
	UPROPERTY(BlueprintAssignable)
		FOnInteraction OnInteractionEnd;
	/*succesful completion of interaction reached*/
	UPROPERTY(BlueprintAssignable)
		FOnInteraction OnInteractionCompleted;
	/*interaction interrupted before completion*/
	UPROPERTY(BlueprintAssignable)
		FOnInteraction OnInteractionCanceled;

	//=================================================================================================
	//============================================FUNCTIONS============================================
	//=================================================================================================

	UInteractiveBoxComponent();

	//=================================================
	//===================INTERACTION===================
	//=================================================
	virtual bool IsInteractive(class AActor* User) override;
	virtual bool IsInteractionEnabled() override;
	virtual bool BeginInteraction(class AActor* User) override;
	virtual void EndInteraction(class AActor* User, bool bInteractionCanceled = false) override;

	virtual float GetCurrentInteractionTime() override;
	virtual float GetRemainingInteractionTime() override;
};
