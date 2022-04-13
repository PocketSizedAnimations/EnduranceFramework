// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FirstPersonViewComponent.generated.h"


UCLASS( ClassGroup=(FirstPerson), meta=(BlueprintSpawnableComponent), HideCategories=(Sockets,Tags,ComponentTick,ComponentReplication,Activation,Cooking,AssetUserData,Collision))
class FIRSTPERSONMODULE_API UFirstPersonViewComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	//view height from center of root component we'll place the First Person View
	UPROPERTY(EditDefaultsOnly)
		float ViewHeight = 80.0f;
	/*pushes the whole scene forward/backward during placement*/
	UPROPERTY(EditDefaultsOnly)
		float ViewForwardOffset = 0.0f;

	/*allows a player to toggle "FreeLook" mode which pivots the camera while keeping the arms static*/
	UPROPERTY(EditDefaultsOnly)
		bool bAllowFreeLook = false;
	UPROPERTY()
		bool bFreeLooking = false;


	class UFirstPersonSceneComponent* Scene;
	class UFirstPersonCameraComponent* Camera;		
	class UFirstPersonArmsComponent* Arms;

	UPROPERTY(EditDefaultsOnly,Category = "Arms")
		USkeletalMesh* ArmsMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Arms")
		TSubclassOf<class UFirstPersonArmsAnimInstance> ArmsAnimationClass;
	UPROPERTY(EditDefaultsOnly, Category = "Arms")
		FVector ArmsOffset;

	//===================================================================================================
	//=============================================FUNCTIONS=============================================
	//===================================================================================================
public:	
	// Sets default values for this component's properties
	UFirstPersonViewComponent(const FObjectInitializer& ObjectInitializer);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
		virtual void InitializeFirstPersonScene();
	UFUNCTION()
		virtual void InitializeCameraComponent();
	UFUNCTION()
		virtual void InitializeArmsMesh();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
