// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

UCLASS()
class SNAKESHOOTER_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	

protected:
	UPROPERTY()
	TArray<TObjectPtr<class USpawnAreaComponent>> SpawnAreaComponents;

protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> SpawnableClasses;


public:	
	AActorSpawner();

public:
	const TArray<TSubclassOf<AActor>>& GetSpawnableClasses() const;

public:
	bool CanSpawn(TSubclassOf<AActor> InActorClass) const;

	template<class T>
	T* Spawn(TSubclassOf<T> InActorClass) const
	{
		check(CanSpawn(InActorClass));
		return GetWorld()->SpawnActor<T>(InActorClass, GetSpawnPoint(), FRotator::ZeroRotator);
	}

	FVector GetSpawnPoint() const;

	
	void AddSpawnArea(USpawnAreaComponent* InSpawnArea);
	void RemoveSpawnArea(USpawnAreaComponent* InSpawnArea);
};
