// Copyright (c) 2022 Pocket Sized Animations


#include "Subsystems/GameMasterSubsystem.h"
#include "GameFramework/PlayerStart.h"
#include "Players/GMPlayerController.h"
#include "EngineUtils.h"





void UGameMasterSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGameMasterSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UGameMasterSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	InitPlayerStartList();
}




//===========================================
//==============PLAYER SPAWNING==============
//===========================================
void UGameMasterSubsystem::InitPlayerStartList()
{
	if (GetWorld())
	{
		for (TActorIterator<APlayerStart> ActItr(GetWorld()); ActItr; ++ActItr)
		{
			FPlayerStartSpawn newSpawnInfo = FPlayerStartSpawn(*ActItr);
			PlayerStarts.Add(newSpawnInfo);
		}
	}
}

APlayerStart* UGameMasterSubsystem::FindRandomPlayerStart(AController* InController, FString FilterTag)
{			
	return nullptr;
}


APawn* UGameMasterSubsystem::SpawnPawn(TSubclassOf<class APawn> PawnClass,FTransform SpawnTransform, AActor* Owner, AController* PossiveController)
{
	
	return nullptr;
}


//==================================
//=============GM LOGIN=============
//==================================
void UGameMasterSubsystem::LogIn(APlayerController* PlayerController, FString Password)
{
	if (GetWorld()->GetNetMode() == NM_Client)
	{
		UE_LOG(LogTemp,Warning,TEXT("Cannot login to GameMasterSubsytem from Client"))
		return;
	}
}

bool UGameMasterSubsystem::IsGMPasswordValid(FString Password)
{
	if (Password == GMPassword)
		return true;
	else
		return false;
}

void UGameMasterSubsystem::SpawnNewGameMasterController(APlayerController* OwningPlayer)
{
	if (GetWorld()->GetNetMode() == NM_Client)
		return;

	AGMPlayerController* GMC = GetWorld()->SpawnActor<AGMPlayerController>(AGMPlayerController::StaticClass());
	GMC->SetOwner(OwningPlayer);
	GMC->NetPlayerIndex = OwningPlayer->NetPlayerIndex; //@warning: critical that this is first as SetPlayer() may trigger RPCs
	GMC->NetConnection = OwningPlayer->NetConnection;
	GMC->SetReplicates(OwningPlayer->GetIsReplicated());
	//GMC->SetPlayer(OwningPlayer->Player);
	GMC->CopyRemoteRoleFrom(OwningPlayer);
}
