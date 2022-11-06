// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "../../DataAssets/ThreatEvaluation.h"
#include "BTService_EvaluateThreats.generated.h"

/**
 * 
 */
UCLASS(AutoExpandCategories=("Threat Scoring|Visibility, Threat Scoring|Distance, Threat Scoring|Weapons"))
class EXTENDEDAIMODULE_API UBTService_EvaluateThreats : public UBTService
{
	GENERATED_BODY()
public:

	
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
		bool bEvaluateVisibleEnemies = true;
	/*threat level bonus for visible enemies*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Visibility", meta = (EditCondition = "bEvaluateVisibleEnemies", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float VisibleEnemyThreat = 1.0f;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
		bool bEvaluateRecentlyLostEnemies = false;
	/*threat level bonus for recently lost enemies*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Visibility", meta = (EditCondition = "bEvaluateRecentlyLostEnemies", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float RecentlyLostEnemyThreat = 0.0f;
	
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
		bool bEvaluateDistance = true;
	/*if Threat is beyond this distance - a scoring of 0.0 is given. Anything inbetween this and the CapsuleRadius will be slowly graded to the DistanceScore (so 1/2 this == 0.5f of Distance Score)*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Distance", meta = (EditCondition = "bEvaluateDistance", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MaxDistance = 2500.0f;
	/*the scoring factor for when the Threat is right on top of us - will be automatically graded with MaxDistance*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Distance", meta = (EditCondition = "bEvaluateDistance", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float DistanceScore = 1.0f;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
		bool bEvaluateClosestEnemy = true;
	/*threat level for closest enemy*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Distance", meta = (EditCondition="bEvaluateClosestEnemy",ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float ClosestEnemyThreat = 1.0f;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
		bool bEvaluateFurthestEnemy = false;
	/*threat level for furthest enemy*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Distance", meta = (EditCondition="bEvaluateFurthestEnemy",ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float FurthestEnemyThreat = 0.0f;
	

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
		bool bEvaluateHeavyWeapons = false;
	/*threat level for heavy weapon enemies*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Weapons", meta = (EditCondition = "bEvaluateHeavyWeapons", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float HeavyWeaponThreat = 1.0f;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
		bool bEvaluateLightWeapons = false;
	/*threat level for light weapon enemies*/
	UPROPERTY(EditAnywhere, Category = "Threat Scoring|Weapons", meta = (EditCondition = "bEvaluateLightWeapons", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float LightWeaponThreat = 1.0f;


	/*cached behavior component reference*/
	UPROPERTY()
		class UAIBehaviorCompoment* BehaviorComponent;


	UBTService_EvaluateThreats();	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData);
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
		virtual float EvaluateThreats(AAIController* AIController);
	UFUNCTION()
		TArray<UThreatEvaluation*> GetKnownThreats(AAIController* AIController);
	UFUNCTION()
		class UAIBehaviorCompoment* GetOwnerBehaviorComponent(AAIController* AIController);
};
