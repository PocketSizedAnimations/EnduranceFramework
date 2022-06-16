// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPONSMODULE_API UProjectileManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:



	//===================================================================================================
	//=============================================FUNCTIONS=============================================
	//===================================================================================================

public:	
	// Sets default values for this component's properties
	UProjectileManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
