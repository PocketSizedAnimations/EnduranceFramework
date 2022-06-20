// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProjectileSpawnerComponent.generated.h"

UENUM(BlueprintType)
enum class EProjectileTraceType : uint8
{
	PlayerView,
	Component,
	Socket
};

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	Projectile,
	Instahit
};

UENUM(BlueprintType)
enum class EFireType : uint8 
{
	Single,
	Semi,
	Burst,
	FullAuto
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPONSMODULE_API UProjectileSpawnerComponent : public USceneComponent
{
	GENERATED_BODY()
public:

private:
	UPROPERTY(Replicated, ReplicatedUsing = "OnRep_FiringStateChanged")
		bool bFiring;


	/*firing info*/
	UPROPERTY(Replicated)
		uint32 ProjectileSpreadSeed; //used to create bullet-spread that's reliable across network
	FRandomStream ProjectileSpreadStream; //used to create a stream of "random" numbers fed in by the replicated seed above
	

	UPROPERTY()
		APlayerController* PC;
	UPROPERTY()
		class UProjectileSubsystem* ProjectileSubsystem;

										  
	/*projectile setup*/
	/*determines if the projectile's tracing should spawn from center of the player's screen (view), this component, or from a socket on the skeletal mesh*/
	UPROPERTY(EditDefaultsOnly, Category = "Projectiles")
		EProjectileType ProjectileType = EProjectileType::Projectile;
	UPROPERTY(EditDefaultsOnly, Category = "Projectiles")
		EProjectileTraceType ProjectileTraceType = EProjectileTraceType::PlayerView;
	UPROPERTY(EditAnywhere, Category = "Projectiles", meta = (EditionCondition="ProjectileTraceType == EProjectileTraceType::Socket"))
		FName ProjectileSocketName = FName("MuzzleSocket");

	UPROPERTY(EditAnywhere, Category = "Projectiles")
		EFireType FireType = EFireType::Semi;
	/*projectiles per-minute*/
	UPROPERTY(EditAnywhere, Category = "Projectiles")
		float FireRate = 600.0f;
	/*the projectile class we'll fire*/	
	UPROPERTY(EditAnywhere, Category = "Projectiles", meta = (DisplayName = "Projectile"))
		class UProjectileInfo* ProjectileInfo;

	//===================================================================================================
	//=============================================FUNCTIONS=============================================
	//===================================================================================================

public:	
	// Sets default values for this component's properties
	UProjectileSpawnerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*starts/stops the call to fire*/
	UFUNCTION()
		virtual void BeginFire();
	UFUNCTION()
		virtual void EndFire();
	/*server-notifications of start/stops*/
	UFUNCTION(Server, Reliable, WithValidation)
		virtual void ServerNotify_BeginFire();
	UFUNCTION(Server, Reliable, WithValidation)
		virtual void ServerNotify_EndFire();
	UFUNCTION(BlueprintPure)
		bool IsFiring();

protected:
	/*performs the actual firing logic*/
	UFUNCTION()
		virtual void PerformFire();
	UFUNCTION()
		virtual void PerformShot();

protected:
	UFUNCTION()
		virtual void OnRep_FiringStateChanged();

	
public:
	UFUNCTION(BlueprintPure)
		virtual FTransform GetProjectileSpawnTransform();
	UFUNCTION(BlueprintPure)
		virtual APlayerController* GetOwningPlayerController();
	UFUNCTION(BlueprintPure)
		virtual APawn* GetOwningPawn();
	UFUNCTION(BlueprintPure)
		bool IsLocallyControlled();
	UFUNCTION(BlueprintPure)
		virtual FTransform GetSocketTransformFromOwner();


	UFUNCTION()
		class UProjectileSubsystem* GetProjectileSubsystem();

};
