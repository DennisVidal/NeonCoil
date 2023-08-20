// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpawnArea/LineSpawnAreaComponent.h"


FVector ULineSpawnAreaComponent::GetSpawnPoint() const
{
	return GetComponentLocation() + FMath::Lerp(LineStart, LineEnd, FMath::FRand());
}