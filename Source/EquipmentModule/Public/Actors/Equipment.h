// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

UCLASS(abstract, Blueprintable)
class EQUIPMENTMODULE_API AEquipment : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY()
		bool bTurnedOn = false;


	UPROPERTY(EditDefaultsOnly, Category = "Battery")
		bool bRequiresBattery = false;
	UPROPERTY(EditDefaultsOnly, Category = "Battery", meta = (EditCondition = bRequiresBattery))
		bool bBatteryInstalled = true;

	//===================================================================================================
	//=============================================FUNCTIONS=============================================
	//===================================================================================================
public:	
	// Sets default values for this actor's properties
	AEquipment(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UFUNCTION()
		virtual void TurnOn();
	UFUNCTION()
		virtual void TurnOff();
};
