// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/InteractiveManagerComponent.h"
#include "Interfaces/InteractiveShapeInterface.h"
#include "InteractiveBoxComponent.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	//instantly complete the action
	Instant,
	//time-based trigger
	Duration,
	//begins interaction and waits to be canceled/completed externally
	Manual
};

/**
 * 
 */
UCLASS(ClassGroup = (Interactions), HideCategories = ("Sockets","Navigation",Rendering,Physics,"Component Tick"), meta = (BlueprintSpawnableComponent))
class INTERACTIONSMODULE_API UInteractiveBoxComponent : public UBoxComponent, public IInteractiveShapeInterface
{
	GENERATED_BODY()
public:
	/*whether or not this object can be interacted with currently - attempting to use an interactive that has this set as false will immedietely cancel the action - still shows up in traces*/
	UPROPERTY(Replicated, EditAnywhere, Category = "Interactions")
		bool bIsInteractive = true;
	/*when disabled - will be disregarded by a InteractiveManager's trace entirely - preventing it from showing up in the list*/
	UPROPERTY(Replicated, EditAnywhere, Category = "Interactions")
		bool bInteractionDisabled = false;


	/*replicated variable indicating this is already being interacted with - used to prevent further use by others*/
	UPROPERTY(Replicated)
		bool bInteractionActive;
	UPROPERTY(Replicated)
		AActor* CurrentUser;
	UPROPERTY(EditAnywhere, Category = "Interactions")
		EInteractionType InteractionType;

	/*local variable to be updated by local client only - indicates when this is being hovered*/
	bool bHovered = false;
	
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

	UPROPERTY(BlueprintAssignable)
		FOnInteraction OnHover;
	UPROPERTY(BlueprintAssignable)
		FOnInteraction OnUnhover;

	//=================================================================================================
	//============================================FUNCTIONS============================================
	//=================================================================================================

	UInteractiveBoxComponent();

	//=================================================
	//===================INTERACTION===================
	//=================================================
	/*whether or not the object has any interactions available or potentially busy*/
	virtual bool IsInteractionAvailable(class AActor* User) override;
	/*checks to see if interactions are enabled - hides it from InteractionManager if true*/
	virtual bool IsInteractionEnabled() override;
	/*called hwen au ser begins interaction*/
	virtual bool BeginInteraction(class AActor* User) override;
	/*called when a user ends interaction*/
	virtual void EndInteraction(class AActor* User) override;
	/*cancel interaction either by early EndInteraction or other factors*/
	virtual void CancelInteraction(class AActor* User) override;
	/*interaction has completed*/
	virtual void CompleteInteraction(class AActor* User) override;

	virtual void OnHoverBegin(class AActor* User) override;
	virtual void OnHoverEnd(class AActor* User) override;

	virtual float GetCurrentInteractionTime() override;
	virtual float GetRemainingInteractionTime() override;


	UFUNCTION()
		virtual void SetActiveUser(AActor* User);
	UFUNCTION()
		virtual void RemoveActiveUser(AActor* User);

};
