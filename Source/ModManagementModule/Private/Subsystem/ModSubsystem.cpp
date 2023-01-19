// Copyright (c) 2022 Pocket Sized Animations


#include "Subsystem/ModSubsystem.h"
#include "Maps/MapInfo.h"

void UModSubsystem::AddMap(AMapInfo* NewMap)
{
	/*safety check*/
	if (NewMap == nullptr)
		return;

	AvailableMaps.Add(NewMap);
}

TArray<class AMapInfo*> UModSubsystem::GetMapsOfCategory(FName Category)
{
	TArray<AMapInfo*> MapListReturn = TArray<AMapInfo*>();

	/*find all Available Maps that match the category - return as an array*/
	for (AMapInfo* Map : AvailableMaps)
	{
		if (Map == nullptr)
			continue;

		/*if we have a Category supplied then filter by category*/
		if (Category.IsNone()  == false && Category != Map->Category)
			continue;
		
		MapListReturn.Add(Map);
	}

	return MapListReturn;	
}
