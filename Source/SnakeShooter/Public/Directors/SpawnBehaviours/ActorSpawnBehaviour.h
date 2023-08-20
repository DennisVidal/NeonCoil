// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActorSpawnBehaviour.generated.h"

UCLASS(EditInlineNew, DefaultToInstanced)
class SNAKESHOOTER_API UActorSpawnBehaviour : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<class UActorDirector> Director;


public:
	FORCEINLINE void SetDirector(class UActorDirector* InDirector) { Director = InDirector; }
	FORCEINLINE class UActorDirector* GetDirector() const { return Director; }

public:
	virtual void Start() {}
	virtual void End() {}
	virtual void Update() {}
};



UCLASS()
class SNAKESHOOTER_API UEndlessActorSpawnBehaviour : public UActorSpawnBehaviour
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	float SpawnInterval = 1.0f;

protected:
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

public:
	virtual void Start() override;
	virtual void End() override;
	virtual void Update() override;
};




UCLASS()
class SNAKESHOOTER_API UWaveActorSpawnBehaviour : public UActorSpawnBehaviour
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	int32 EnemyCount = 0;
	UPROPERTY(EditAnywhere)
	float WaveTime = 10.0f;

	UPROPERTY()
	int32 SpawnedEnemyCount = 0;
protected:
	UPROPERTY()
	FTimerHandle WaveTimerHandle;

public:
	virtual void Start() override;
	virtual void End() override;
	virtual void Update() override;
};


UCLASS()
class SNAKESHOOTER_API UScalingActorSpawnBehaviour : public UActorSpawnBehaviour
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	float MaxSpawnInterval = 2.5f;

	UPROPERTY(EditAnywhere)
	float MinSpawnInterval = 1.0f;

	UPROPERTY(EditAnywhere)
	float ScalingTime = 60.0f;

	UPROPERTY()
	float ElapsedTime = 0.0f;

protected:
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

public:
	virtual void Start() override;
	virtual void End() override;
	virtual void Update() override;
};