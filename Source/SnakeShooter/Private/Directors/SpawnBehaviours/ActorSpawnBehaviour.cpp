// Fill out your copyright notice in the Description page of Project Settings.


#include "Directors/SpawnBehaviours/ActorSpawnBehaviour.h"
#include "Directors/ActorDirector.h"


void UEndlessActorSpawnBehaviour::Start()
{
	check(GetWorld());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(SpawnTimerHandle, this, &UEndlessActorSpawnBehaviour::Update, SpawnInterval, true);
	Director->OnSpawnBehaviourStarted(this);
}

void UEndlessActorSpawnBehaviour::End()
{
	check(GetWorld());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(SpawnTimerHandle);
	Director->OnSpawnBehaviourEnded(this);
}

void UEndlessActorSpawnBehaviour::Update()
{
	check(Director);
	Director->SpawnRandom();
}







void UWaveActorSpawnBehaviour::Start()
{
	check(GetWorld());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(WaveTimerHandle, this, &UWaveActorSpawnBehaviour::Update, WaveTime / EnemyCount, true);
	Director->OnSpawnBehaviourStarted(this);
}

void UWaveActorSpawnBehaviour::End()
{
	check(GetWorld());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(WaveTimerHandle);
	Director->OnSpawnBehaviourEnded(this);
}

void UWaveActorSpawnBehaviour::Update()
{
	check(Director);
	Director->SpawnRandom();
	SpawnedEnemyCount += 1;
	if (SpawnedEnemyCount >= EnemyCount)
	{
		End();
	}
}




void UScalingActorSpawnBehaviour::Start()
{
	check(GetWorld());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(SpawnTimerHandle, this, &UScalingActorSpawnBehaviour::Update, MaxSpawnInterval, false);
	Director->OnSpawnBehaviourStarted(this);
}

void UScalingActorSpawnBehaviour::End()
{
	check(GetWorld());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(SpawnTimerHandle);
	Director->OnSpawnBehaviourEnded(this);
}

void UScalingActorSpawnBehaviour::Update()
{
	check(Director);
	Director->SpawnRandom();

	check(GetWorld());
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	float ElapsedTimeDelta = TimerManager.GetTimerRate(SpawnTimerHandle);
	ElapsedTime += ElapsedTimeDelta;
	float T = FMath::Clamp(ElapsedTime / ScalingTime, 0.0f, 1.0f);
	float NewSpawnInterval = FMath::Lerp(MaxSpawnInterval, MinSpawnInterval, T);
	TimerManager.SetTimer(SpawnTimerHandle, this, &UScalingActorSpawnBehaviour::Update, NewSpawnInterval, false);
}
