// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MovableDoorComponent.generated.h"

UENUM(BlueprintType)
enum class EDoorType : uint8
{
	Swing,
	Slide
};

UENUM(BlueprintType)
enum class EDoorState : uint8
{
	Closed,
	Closing,
	Opening,
	Opened,
};

UENUM(BlueprintType)
enum class EDoorHingeAxis : uint8 
{
	X,
	XNeg UMETA(DisplayName = "-X"),
	Y,
	YNeg UMETA(DisplayName = "-Y"),
	Z,
	ZNeg UMETA(DisplayName = "-Z")
};


UCLASS(ClassGroup=(Interactives), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSMODULE_API UMovableDoorComponent : public USceneComponent
{
	GENERATED_BODY()
public:

	UPROPERTY()
		bool bLocked;
	/*replicated state used to notify the client of changes*/
	UPROPERTY(Replicated, ReplicatedUsing = "OnRep_DoorStateChange")
		bool bReplicatedDoorOpen = false;
	/*state used for animation & visuals*/
	UPROPERTY()
		EDoorState State;
	
	/*where the hinge exists in local axis space*/
	UPROPERTY(VisibleAnywhere, Category = "Door Configuration")
		EDoorHingeAxis HingeAxis = EDoorHingeAxis::Y;
	UPROPERTY(EditAnywhere, Category = "Door Configuration")
		EDoorType Type;
	/*not recommended to go to 90 as you tend to clip geometry*/
	UPROPERTY(EditAnywhere, Category = "Door Configuration", meta =(UIMin= 1,UIMax=90))
		float MaxOpenSwingAngle = 89;
	UPROPERTY(EditAnywhere, Category = "Door Configuration")
		float MaxOpenSlidePosition = 80;
	
	/*the offset we have to position the hinge*/
	UPROPERTY(VisibleAnywhere)
		float SceneBoundsOffset = 0.0f;
	UPROPERTY(VisibleAnywhere)
		float InteractionCollisionOffset = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		FTransform DoorMeshTransform;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		FVector InteractiveExtent = FVector(15, 65, 105);

	/*editor curves*/
	UPROPERTY(EditAnywhere, Category = "Animations")
		FRuntimeFloatCurve EditorOpenAnimCurve;
	UPROPERTY(EditAnywhere, Category = "Animations")
		FRuntimeFloatCurve EditorCloseAnimCurve;


	/*runtime curves*/
	UPROPERTY()
		UCurveFloat* OpenAnimCurve;	
	UPROPERTY()
		UCurveFloat* CloseAnimCurve;

	FName OpenCurveName = FName("OpenDoor");
	FName CloseCurveName = FName("CloseDoor");


	UPROPERTY()
		class UInteractiveBoxComponent* InteractiveShapeComponent;
	UPROPERTY()
		UStaticMeshComponent* Mesh;
	UPROPERTY()
		class UArrowComponent* ArrowComponent;
	UPROPERTY()
		class UArrowComponent* HingeArrowComponent;
	UPROPERTY()
		USceneComponent* SceneComponent;
	UPROPERTY()
		class UTimelineComponent* TimelineComponent;

	//=================================================================================================
	//============================================FUNCTIONS============================================
	//=================================================================================================
		

public:	
	// Sets default values for this component's properties
	UMovableDoorComponent(const FObjectInitializer& ObjectInitializer);
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



	//===============================================
	//==================INTERACTION==================
	//===============================================
protected:
	/*called whenever a local user attempts to interact with this object*/
	UFUNCTION()
		virtual void OnInteractionBegin(AActor* self, AActor* User);
	UFUNCTION()
		virtual void OnInteractionEnd(AActor* self, AActor* User);

	//====================================================
	//==================DOOR INTERACTION==================
	//====================================================
public:
	/*called by a client to open the door*/
	UFUNCTION(Server,Reliable,WithValidation)
		virtual void ServerOpenDoor(AActor* User);
	/*called to attempt open the door*/
	UFUNCTION()
		virtual void OpenDoor();
	UFUNCTION()
		virtual void CloseDoor();
	/*blueprint callable version of OpenDoor that prevents clients from opening the door directly*/
	UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (DisplayName = "Open Door"))
		void BP_OpenDoor();
	/*blueprint callable version of CloseDoor that prevents clients from closing the door directly*/
	UFUNCTION(BlueprintCallable, Category = "Interaction", meta = (DisplayName = "Open Door"))
		void BP_CloseDoor();


	UFUNCTION()
		virtual void OnRep_DoorStateChange();

	//==============================================
	//================DOOR FUNCTIONS================
	//==============================================
private:
	/*function that actually opens the door*/
	UFUNCTION()
		virtual void BeginOpen();
	UFUNCTION()
		virtual void BeginClose();

	//==========================
	//========ANIMATIONS========
	//==========================
	UFUNCTION()
		virtual void InitAnimationCurves();
	UFUNCTION()
		virtual void OnUpdateDoorAnimation();
	UFUNCTION()
		virtual void OnDoorAnimationFinished();

	
	//=========================
	//======CONFIGURATION======
	//=========================
	UFUNCTION()
		void AlignScenePosition();


};
