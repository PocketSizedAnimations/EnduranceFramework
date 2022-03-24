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
	/*determines if this object is in a state of being able to be used*/
	UFUNCTION()
		virtual bool IsInteractive(AActor* User) {return true;};
	UFUNCTION()
		virtual bool IsInteractionEnabled() { return true; };
	/*return fales if the interaction attempt was denied*/
	UFUNCTION()
		virtual bool BeginInteraction(AActor* User) { return false; };
	UFUNCTION()
		virtual void EndInteraction(AActor* User, bool bInteractionCanceled = false) { };

	/*how long we've been interacting*/
	UFUNCTION()
		virtual float GetCurrentInteractionTime() { return 0; };
	/*how much longer we have left to interact*/
	UFUNCTION()
		virtual float GetRemainingInteractionTime() { return 0; };

};
