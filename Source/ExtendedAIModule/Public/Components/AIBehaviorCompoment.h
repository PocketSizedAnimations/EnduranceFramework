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
	/*states*/
	UPROPERTY(EditAnywhere, Instanced, Category = "State", meta = (DisplayName = "Default State"))
		class UAIState* State;
	UPROPERTY()
		class UAIState* PreviousState;

	/*goals*/
private:
	UPROPERTY(EditInstanceOnly, Instanced, Category = "Goal")
		class UAIGoal* Goal;
	UPROPERTY()
		class UAIGoal* PreviousGoal;

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

private:
	UPROPERTY(EditAnywhere, Category = "Aggression", meta=(UIMin=0,UIMax=100))
		float Aggression = 62.0f;	
	UPROPERTY(EditAnywhere, Category = "Aggression", meta=(UIMin=0,UIMax=100))
		float MinAggression = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Aggression", meta = (UIMin=0, UIMax=100))
		float MaxAggression = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Aggression")
		bool bRandomAggressionOnSpawn = false;


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

	//====================================================
	//=======================STATES=======================
	//====================================================
public:
	UFUNCTION(BlueprintCallable, Category = "States")
		virtual void SetState(class UAIState* NewState);
	UFUNCTION(BlueprintPure, Category = "States")
		class UAIState* GetState();
	UFUNCTION(BlueprintPure, Category = "States")
		class UAIState* GetPreviousState();
	UFUNCTION(BlueprintCallable, Category = "States")
		void ClearState();
	UFUNCTION(BlueprintCallable, Category = "States")
		void ClearPreviousState();

	//=====================================================
	//========================GOALS========================
	//=====================================================
public:
	UFUNCTION(BlueprintCallable, Category = "Goals")
		virtual void SetGoal(class UAIGoal* NewGoal);
	UFUNCTION(BlueprintPure, Category = "Goals")
		class UAIGoal* GetGoal();
	UFUNCTION(BlueprintPure, Category = "Goals")
		class UAIGoal* GetPreviousGoal();
	UFUNCTION(BlueprintCallable, Category = "Goals")
		void ClearGoal();



	//=====================================================
	//======================AGGRESSION=====================
	//=====================================================
public:
	UFUNCTION(BlueprintPure, Category = "Aggression")
		float GetAggressionLevel();
	UFUNCTION(BlueprintPure, Category = "Aggression")
		float GetMaxAggressionLevel();
	UFUNCTION(BlueprintPure, Category = "Aggression")
		float GetMinAggressionLevel();
	UFUNCTION(BlueprintCallable, Category = "Aggression")
		void SetAggression(float NewAggression);
	UFUNCTION(BlueprintCallable, Category = "Aggression")
		float SetRandomAggressionLevel();

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
