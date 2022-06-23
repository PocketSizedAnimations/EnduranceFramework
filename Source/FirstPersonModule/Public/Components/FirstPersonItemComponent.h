// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FirstPersonItemComponent.generated.h"


UCLASS( ClassGroup=(FirstPerson), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONMODULE_API UFirstPersonItemComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	/*the mesh to automatically attach to the first person arms on equip*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Person")
		class USkeletalMesh* FirstPersonMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "First Person")
		FName MeshName = "FirstPersonMesh";
	UPROPERTY(EditDefaultsOnly, Category = "First Person")
		TSubclassOf<class UAnimInstance> AnimationBlueprint;

	class USkeletalMeshComponent* SkeletalMeshComp;

	//=================================================================================
	//====================================FUNCTIONS====================================
	//=================================================================================


public:	
	// Sets default values for this component's properties
	UFirstPersonItemComponent();

protected:
	virtual void InitializeComponent() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION()
		void InitializeFirstPersonMesh();
	UFUNCTION(BlueprintCallable, Category = "First Person")
		void AttachFirstPersonMesh();
	UFUNCTION()
		FName GetAttachmentSocketName();
	UFUNCTION()
		APawn* GetOwningPawn();
		
};
