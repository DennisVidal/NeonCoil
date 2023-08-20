// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorDirector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDelegate, AActor*, InActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDirectorDelegate, UActorDirector*, InDirector);


USTRUCT()
struct FActorDirectorActorData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ActorVariants;

public:
	UPROPERTY()
	TArray<TObjectPtr<class AActorSpawner>> Spawners;
};



UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UActorDirector : public UObject
{
	GENERATED_BODY()


public:
	UPROPERTY()
	FActorDelegate OnActorSpawnedDelegate;

	UPROPERTY()
	FActorDirectorDelegate OnAllSpawnBehavioursEndedDelegate;

protected:
	UPROPERTY(EditAnywhere)
	TArray<FActorDirectorActorData> ActorData;


	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<class UActorSpawnBehaviour>> SpawnBehaviours;

	UPROPERTY(VisibleAnywhere)
		int32 CurrentSpawnBehaviourIndex = INDEX_NONE;


	UPROPERTY(EditAnywhere)
		int32 MaxConcurrentActorCount = -1;
	UPROPERTY(VisibleAnywhere)
		int32 SpawnedActorCount = 0;


public:
	virtual void Initialize();

protected:
	 void RegisterSpawners();
	void InitializeBehaviours();

public:
	void StartBehaviours();

	void SpawnRandom();

public:
	void RegisterSpawner(class AActorSpawner* InSpawner);
	void UnregisterSpawner(class AActorSpawner* InSpawner);

public:
	void OnSpawnBehaviourStarted(class UActorSpawnBehaviour* InBehaviour);
	void OnSpawnBehaviourEnded(class UActorSpawnBehaviour* InBehaviour);

protected:
	UFUNCTION()
	void OnActorDestroyed(AActor* InDestroyedActor);
};