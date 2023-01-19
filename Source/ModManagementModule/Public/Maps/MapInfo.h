// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "UObject/SoftObjectPtr.h"
#include "Engine/World.h"
#include "MapInfo.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class MODMANAGEMENTMODULE_API AMapInfo : public AInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere,meta=(ExposeOnSpawn=true))
		FName MapName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn = true))
		FName Category;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn = true, Multiline=true))
		FText Description;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn = true))
		FName Author;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn = true))
		class UTexture2D* PreviewImage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (ExposeOnSpawn = true))
		TSoftObjectPtr<class UWorld> LevelMap;
};
