// Copyright (c) 2022 Pocket Sized Animations

/*The GameMaster Subsystem - A GameMaster is one that pushes the game along in specific directions, a GameMaster's job is not to rule the game, but rather set a tone in an attempt
to provide a more enjoyable (and often challenging) experience to the players. The GameMaster Subsystem is the toolkit that allows for this - exposing abilities to a GM to manipulate
the world*/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameMasterSubsystem.generated.h"


USTRUCT(BlueprintType)
struct FPlayerStartSpawn
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
		class APlayerStart* PlayerStart;
	UPROPERTY(BlueprintReadOnly)
		float LastUsedTimeStamp = 0.0f;
	UPROPERTY(BlueprintReadOnly)
		class APawn* LastUsedPawn = nullptr;

	FPlayerStartSpawn() {}
	FPlayerStartSpawn(class APlayerStart* inPlayerStart) : PlayerStart(inPlayerStart) {}
};

/**
 * 
 */
UCLASS()
class GAMEMASTERMODULE_API UGameMasterSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:




	/*player-spawning*/
	UPROPERTY()
		TArray<FPlayerStartSpawn> PlayerStarts;


	/*log-ins*/
private:
	FString GMPassword = "ButtBuddy";

	//===========================================================================================================
	//=================================================FUNCTIONS=================================================
	//===========================================================================================================
public:
	//====================================
	//===========INITIALIZATION===========
	//====================================
	// 
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	//==============================================
	//==============CHARACTER SPAWNING==============
	//==============================================
	UFUNCTION(BlueprintCallable)
		virtual void InitPlayerStartList();
	/*Finds a Random PlayerStart - optional FilterTag*/
	UFUNCTION(BlueprintCallable)
		virtual class APlayerStart* FindRandomPlayerStart(AController* InController, FString FilterTag = "");
	/*Spawns a Pawn - if Controller is given - will automatically push to have them possess it*/
	UFUNCTION(BlueprintCallable)
		virtual class APawn* SpawnPawn(TSubclassOf<class APawn> PawnClass, FTransform SpawnTransform, AActor* Owner = nullptr, AController* PossiveController = nullptr);
	

	//==================================
	//=============GM LOGIN=============
	//==================================
public:
	UFUNCTION(BlueprintCallable)
		void LogIn(APlayerController* PlayerController, FString Password);
private:
	UFUNCTION()
		bool IsGMPasswordValid(FString Password);



public:
	UFUNCTION(BlueprintCallable)
		void SpawnNewGameMasterController(APlayerController* OwningPlayer);

	
};
