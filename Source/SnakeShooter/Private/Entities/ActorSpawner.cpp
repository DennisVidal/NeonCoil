// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/ActorSpawner.h"
#include "Components/SpawnArea/SpawnAreaComponent.h"

AActorSpawner::AActorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

const TArray<TSubclassOf<AActor>>& AActorSpawner::GetSpawnableClasses() const
{
	return SpawnableClasses;
}

bool AActorSpawner::CanSpawn(TSubclassOf<AActor> InActorClass) const
{
	for (TSubclassOf<AActor> SpawnableClass : SpawnableClasses)
	{
		if (InActorClass->IsChildOf(SpawnableClass))
		{
			return true;
		}
	}
	return false;
}


FVector AActorSpawner::GetSpawnPoint() const
{
	if (!SpawnAreaComponents.Num())
	{
		return GetActorLocation();
	}

	int32 SpawnAreaIndex = FMath::RandRange(0, SpawnAreaComponents.Num() - 1);
	return SpawnAreaComponents[SpawnAreaIndex]->GetSpawnPoint();
}

void AActorSpawner::AddSpawnArea(USpawnAreaComponent* InSpawnArea)
{
	SpawnAreaComponents.Add(InSpawnArea);
}

void AActorSpawner::RemoveSpawnArea(USpawnAreaComponent* InSpawnArea)
{
	SpawnAreaComponents.Remove(InSpawnArea);
}


