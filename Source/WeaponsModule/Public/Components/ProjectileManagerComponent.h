// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "ProjectileManagerComponent.generated.h"


USTRUCT()
struct FProjectile
{
	GENERATED_BODY()
public:

	UPROPERTY()
		class UProjectileInfo* ProjectileInfo;
	UPROPERTY()
		FVector Location;
	UPROPERTY()
		FVector ForwardDirection;
	UPROPERTY()
		float GravityStrength;
	UPROPERTY()
		float Velocity;
	UPROPERTY()
		float TracerVelocity;
	UPROPERTY()
		float DistanceTraveled;
	
	/*impact info*/
	UPROPERTY()
		bool bProjectileHit;
	UPROPERTY()
		FVector HitLocation;
	UPROPERTY()
		float TimeSinceHit;


};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPONSMODULE_API UProjectileManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	const float Gravity = 9.8f;

	UPROPERTY()
		TArray<FProjectile> Projectiles;
	
		FCollisionQueryParams ProjectileCollisionParams;

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


	
public:
	UFUNCTION()
		void SpawnProjectile(FProjectile NewProjectile);

	//=================================================
	//==============PROJECTILE PROCESSING==============
	//=================================================
private:
	UFUNCTION()
		void ProcessProjectileMovement(FProjectile& Projectile);
	UFUNCTION()
		void ProcessProjectileHit(FProjectile& Projectile);

};
