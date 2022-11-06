// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIBehaviorCompoment.generated.h"

USTRUCT(BlueprintType)
struct FEnemyThreat
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
		AActor* Actor;
	UPROPERTY(BlueprintReadOnly)
		float ThreatLevel;

	FEnemyThreat()
	{

	}

	FEnemyThreat(AActor* actor, float threatLevel) :Actor(actor), ThreatLevel(threatLevel) {}
};

UCLASS( DisplayName="Behavior Component", ClassGroup = (ArtificialIntelligence), meta = (BlueprintSpawnableComponent))
class EXTENDEDAIMODULE_API UAIBehaviorCompoment : public UActorComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY()
		class USensesComponent* OwnerSensesComponent;

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

	/*if enabled will automatically add/remove threats based on sibling SensesComponent detected actors*/
	UPROPERTY(EditAnywhere)
		bool bCalcThreatsFromSensesComponent = true;
	UPROPERTY()
		TArray<class UThreatEvaluation*> Threats;




		//===============================================================================================
		//===========================================FUNCTIONS===========================================
		//===============================================================================================
public:	
	// Sets default values for this component's properties
	UAIBehaviorCompoment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void InitBehaviorTree();
	UFUNCTION()
		virtual void InitOwnerSensesComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//=====================================================
	//===================THREAT HANDLING===================
	//=====================================================
	/*Updates list of Threats based on surrounding knowledge*/
	UFUNCTION()
		virtual void CalcThreats();
	UFUNCTION()
		TArray<class UThreatEvaluation*> GetActiveThreats();
	UFUNCTION()
		bool IsThreatKnown(AActor* ThreatActor);
	UFUNCTION()
		virtual void AddThreat(AActor* ThreatActor);


	//====================================================
	//===================ENEMY HANDLING===================
	//====================================================
public:
	UFUNCTION(BlueprintCallable, Category = "Enemies")
		virtual void SetCurrentEnemy(AActor* NewEnemy);
	UFUNCTION(BlueprintCallable, Category = "Enemies")
		void ClearEnemy();
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Enemies")
		AActor* GetCurrentEnemy();
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Enemies")
		AActor* GetPreviousEnemy();






	UFUNCTION()
		class USensesComponent* GetOwnerSensesComponent();


};
