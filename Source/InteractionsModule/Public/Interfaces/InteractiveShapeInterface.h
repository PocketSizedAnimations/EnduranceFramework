// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveShapeInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveShapeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIONSMODULE_API IInteractiveShapeInterface
{
	GENERATED_BODY()
	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*determines if this object has any interactions available or is disabled/busy*/
	UFUNCTION()
		virtual bool IsInteractionAvailable(AActor* User) {return true;};
	UFUNCTION()
		virtual bool IsInteractionEnabled() { return true; };
	/*return fales if the interaction attempt was denied*/
	UFUNCTION()
		virtual bool BeginInteraction(AActor* User) { return false; };
	UFUNCTION()
		virtual void EndInteraction(AActor* User) { };
	UFUNCTION()
		virtual void CancelInteraction(AActor* User) { };
	UFUNCTION()
		virtual void CompleteInteraction(AActor* User) {};

	UFUNCTION()
		virtual void OnHoverBegin(AActor* User) {};
	UFUNCTION()
		virtual void OnHoverEnd(AActor* User) {};

	UFUNCTION()
		virtual bool IsInteractionActive() { return false; };

	/*how long we've been interacting*/
	UFUNCTION()
		virtual float GetCurrentInteractionTime() { return 0; };
	/*how much longer we have left to interact*/
	UFUNCTION()
		virtual float GetRemainingInteractionTime() { return 0; };

};
