// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpawnArea/SpawnAreaComponent.h"
#include "Entities/ActorSpawner.h"

USpawnAreaComponent::USpawnAreaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


FVector USpawnAreaComponent::GetSpawnPoint() const
{
	return GetComponentLocation();
}

void USpawnAreaComponent::OnRegister()
{
	Super::OnRegister();
	if (AActorSpawner* OwningSpawner = GetOwner<AActorSpawner>())
	{
		OwningSpawner->AddSpawnArea(this);
	}
}

void USpawnAreaComponent::OnUnregister()
{
	Super::OnUnregister();
	if (AActorSpawner* OwningSpawner = GetOwner<AActorSpawner>())
	{
		OwningSpawner->RemoveSpawnArea(this);
	}
}
