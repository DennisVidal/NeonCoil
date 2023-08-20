// Fill out your copyright notice in the Description page of Project Settings.


#include "Directors/ActorDirector.h"
#include "Entities/ActorSpawner.h"
#include "EngineUtils.h"
#include "Directors/SpawnBehaviours/ActorSpawnBehaviour.h"


void UActorDirector::Initialize()
{
	InitializeBehaviours();
	RegisterSpawners();
}

void UActorDirector::RegisterSpawners()
{
	//Spawners registering themselves would generally be better
	//But since spawners currently don't know which director they have to register with this is the easier way
	for (TActorIterator<AActorSpawner> Iterator(GetWorld(), AActorSpawner::StaticClass()); Iterator; ++Iterator)
	{
		RegisterSpawner(*Iterator);
	}
}

void UActorDirector::InitializeBehaviours()
{
	for (int32 i = 0; i < SpawnBehaviours.Num(); ++i)
	{
		SpawnBehaviours[i]->SetDirector(this);
	}
}

void UActorDirector::StartBehaviours()
{
	if (SpawnBehaviours.Num())
	{
		CurrentSpawnBehaviourIndex = 0;
		SpawnBehaviours[0]->Start();
	}
}

void UActorDirector::SpawnRandom()
{
	if (!ActorData.Num())
	{
		return;
	}

	if (MaxConcurrentActorCount >= 0 && SpawnedActorCount >= MaxConcurrentActorCount)
	{
		return;
	}


	int32 SelectedActorIndex = FMath::RandRange(0, ActorData.Num() - 1);
	const FActorDirectorActorData& Data = ActorData[SelectedActorIndex];

	if (!Data.Spawners.Num())
	{
		return;
	}

	AActorSpawner* SelectedSpawner = Data.Spawners[FMath::RandRange(0, Data.Spawners.Num() - 1)];
	if (!SelectedSpawner)
	{
		return;
	}

	TSubclassOf<AActor> ActorClass = Data.ActorVariants.Num() ? 
		Data.ActorVariants[FMath::RandRange(0, Data.ActorVariants.Num() - 1)] 
		: Data.ActorClass;


	if (AActor* SpawnedActor = SelectedSpawner->Spawn(ActorClass))
	{
		SpawnedActorCount++;
		SpawnedActor->OnDestroyed.AddDynamic(this, &UActorDirector::OnActorDestroyed);
		OnActorSpawnedDelegate.Broadcast(SpawnedActor);
	}
}

void UActorDirector::RegisterSpawner(AActorSpawner* InSpawner)
{
	for (FActorDirectorActorData& Data : ActorData)
	{
		if (InSpawner->CanSpawn(Data.ActorClass))
		{
			Data.Spawners.Add(InSpawner);
		}
	}
}

void UActorDirector::UnregisterSpawner(AActorSpawner* InSpawner)
{
	for (FActorDirectorActorData& Data : ActorData)
	{
		if (InSpawner->CanSpawn(Data.ActorClass))
		{
			Data.Spawners.RemoveSwap(InSpawner);
		}
	}
}

void UActorDirector::OnSpawnBehaviourStarted(UActorSpawnBehaviour* InBehaviour)
{
}

void UActorDirector::OnSpawnBehaviourEnded(UActorSpawnBehaviour* InBehaviour)
{
	if (SpawnBehaviours[CurrentSpawnBehaviourIndex] == InBehaviour)
	{
		CurrentSpawnBehaviourIndex += 1;
		if (CurrentSpawnBehaviourIndex < SpawnBehaviours.Num())
		{
			SpawnBehaviours[CurrentSpawnBehaviourIndex]->Start();
			return;
		}

		OnAllSpawnBehavioursEndedDelegate.Broadcast(this);
	}
}

void UActorDirector::OnActorDestroyed(AActor* InDestroyedActor)
{
	SpawnedActorCount--;
}
