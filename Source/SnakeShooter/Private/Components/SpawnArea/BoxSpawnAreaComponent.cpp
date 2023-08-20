// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpawnArea/BoxSpawnAreaComponent.h"

FVector UBoxSpawnAreaComponent::GetSpawnPoint() const
{
	return GetComponentLocation() + FMath::RandPointInBox(FBox(BoxMin, BoxMax));
}