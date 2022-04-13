// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FirstPersonSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONMODULE_API UFirstPersonSceneComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UPROPERTY()
		bool bFreeLooking = false;

public:	
	// Sets default values for this component's properties
	UFirstPersonSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
