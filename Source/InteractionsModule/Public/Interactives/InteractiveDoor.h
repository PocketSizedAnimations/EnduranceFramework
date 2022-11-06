// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveDoor.generated.h"

UENUM(BlueprintType)
enum class EDoorState : uint8 
{
	Closed,
	Closing,
	Opening,
	Opened,
};


UCLASS(Blueprintable, HideCategories=(ActorTick,Replication,Rendering,Collision,Actor,Input,HLOD,Cooking))
class INTERACTIONSMODULE_API AInteractiveDoor : public AActor
{
	GENERATED_BODY()
public:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
		EDoorState DoorState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
		bool bLocked;


	/*animations*/
protected:
	UPROPERTY(VisibleAnywhere)
		class UTimelineComponent* TimelineComponent;	
	//UPROPERTY(EditAnywhere, Category = "Animations")
	//	float DoorAnimationLength;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animations")
		float MaxDoorOpenAngle = 98.0f;
	/*editor curve*/
	UPROPERTY(EditAnywhere, Category = "Animations")
		FRuntimeFloatCurve DoorOpenAnimCurve;
	/*runtime curve*/
	UPROPERTY()
		UCurveFloat* OpenAnimCurve;

	/*editor curve*/
	UPROPERTY(EditAnywhere, Category = "Animations")
		FRuntimeFloatCurve DoorCloseAnimCurve;
	/*runtime curve*/
	UPROPERTY()
		UCurveFloat* CloseAnimCurve;



protected:
	/*components*/
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* DoorSceneComponent;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* DoorMeshComponent;
	UPROPERTY(VisibleAnywhere)
		class UInteractiveBoxComponent* InteractiveComponent;

public:	
	// Sets default values for this actor's properties
	AInteractiveDoor(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitAnimationCurves();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION()
		virtual void OnInteractionBegin(AActor* self, AActor* User);
	UFUNCTION()
		virtual void OnInteractionEnd(AActor* self, AActor* User);

protected:
	UFUNCTION(BlueprintCallable, Category = "Interactions")
		virtual void OpenDoor();
private:
	UFUNCTION()
		virtual void BeginOpen();
	UFUNCTION()
		virtual void OnUpdateDoorAnimation();
	UFUNCTION()
		virtual void OnDoorAnimationFinished();
	UFUNCTION()
		virtual void EndOpen();

	UFUNCTION(BlueprintCallable, Category = "Interactions")
		virtual void CancelDoorOpen();

	UFUNCTION(BlueprintCallable, Category = "Interactions")
		virtual void CloseDoor();
	UFUNCTION()
		virtual void BeginClose();
	UFUNCTION()
		virtual void EndClose();


protected:
	UFUNCTION()
		virtual void SetAnimationCurve(UCurveFloat* NewCurve);
};
