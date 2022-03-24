// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/UnrealType.h"
#include "CollisionShape.h"
#include "Engine/CollisionProfile.h"
#include "InteractiveManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteraction, AActor*, Actor, AActor*, User);

UENUM()
enum class EInteractiveTraceType : uint8
{
	Controller,
	Camera
};

UENUM()
enum class EInteractionStatus : uint8
{
	Unknown,
	Completed,
	Canceled,
	Failed
};

USTRUCT()
struct FInteraction 
{
	GENERATED_BODY()
public:

	UPROPERTY()
		UActorComponent* Interactive = nullptr;
	UPROPERTY()
		EInteractionStatus Status;


	FInteraction() {};

};



UCLASS( ClassGroup=(Interactions), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSMODULE_API UInteractiveManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Interactions")
		TEnumAsByte<ETraceTypeQuery> TraceChannel;
	UPROPERTY(EditDefaultsOnly, Category = "Interactions")
		EInteractiveTraceType TraceType;
	UPROPERTY(EditDefaultsOnly, Category = "Interactions")
		float TraceLength;


private:
	/*all possible interactions near us*/
	UPROPERTY()
		TArray<UActorComponent*> Interactives;
	/*the current interaction we're using actively*/
	UPROPERTY()
		UActorComponent* ActiveInteraction;
	

	/*events/delegates*/
public:
	UPROPERTY(BlueprintAssignable)
		FOnInteraction OnInteractionDenied;

	//=========================================================================================================
	//================================================FUNCTIONS================================================
	//=========================================================================================================

public:	
	// Sets default values for this component's properties
	UInteractiveManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//================================================
	//==================INTERACTIONS==================
	//================================================
public:
	UFUNCTION(BlueprintCallable)
		virtual bool Interact(UActorComponent* Interactive);
	UFUNCTION(BlueprintCallable)
		virtual void CancelInteraction(UActorComponent* Interactive);

	//============================================
	//===========INTERACTIVES MANAGEMENT===========
	//============================================
protected:
	UFUNCTION()
		virtual bool IsInteractive(UActorComponent* Interactive);
	UFUNCTION()
		virtual void AddInteractive(UActorComponent*& Interactive);
	UFUNCTION()
		virtual void RemoveInteractive(UActorComponent*& Interactive);
	UFUNCTION()
		virtual void ClearInteractives();
	UFUNCTION()
		virtual void ClearActiveInteraction();
	UFUNCTION()
		virtual void UpdateActiveInteractiveStatus();
public:
	UFUNCTION(BlueprintPure)
		UActorComponent* GetCurrentInteractive();
	UFUNCTION(BlueprintPure)
		virtual bool IsActiveInteractionComplete();


	//===============================
	//============TRACING============
	//===============================
protected:
	UFUNCTION()
		virtual void TraceForInteractives();
	UFUNCTION()
		virtual FVector GetTraceStart();
	UFUNCTION()
		virtual FVector GetTraceEnd();	
	UFUNCTION()
		virtual FRotator GetTraceRotation();
	UFUNCTION()
		virtual ECollisionChannel GetTraceChannel();


		
};
