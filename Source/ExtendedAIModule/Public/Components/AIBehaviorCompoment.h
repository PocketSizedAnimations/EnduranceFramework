// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIBehaviorCompoment.generated.h"


UCLASS( DisplayName="Behavior Component", ClassGroup = (ArtificialIntelligence), meta = (BlueprintSpawnableComponent))
class EXTENDEDAIMODULE_API UAIBehaviorCompoment : public UActorComponent
{
	GENERATED_BODY()
public:

private:
	/*current enemy we would like to be dead*/
	UPROPERTY()
		AActor* CurrentEnemy;
	/*who we were targeting last*/
	UPROPERTY()
		AActor* PreviousEnemy;
	/*the last time we switched enemies*/
	UPROPERTY()
		float EnemySwitchTimeStamp;



		//===============================================================================================
		//===========================================FUNCTIONS===========================================
		//===============================================================================================
public:	
	// Sets default values for this component's properties
	UAIBehaviorCompoment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



	//====================================================
	//===================ENEMY HANDLING===================
	//====================================================

	UFUNCTION(BlueprintCallable, Category = "Enemies")
		virtual void SetCurrentEnemy(AActor* NewEnemy);
	UFUNCTION(BlueprintCallable, Category = "Enemies")
		void ClearEnemy();
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Enemies")
		AActor* GetCurrentEnemy();
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Enemies")
		AActor* GetPreviousEnemy();


};
