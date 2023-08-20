// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpawnArea/CircleSpawnAreaComponent.h"

FVector UCircleSpawnAreaComponent::GetSpawnPoint() const
{
	FVector2D CirclePosition;
	if (bAllowSpawningWithinCircle)
	{
		CirclePosition = FMath::RandPointInCircle(CircleRadius);
	}
	else
	{
		float Angle = FMath::FRandRange(0.0f, TWO_PI);
		CirclePosition = CircleRadius * FVector2D(FMath::Cos(Angle), FMath::Sin(Angle));
	}

	return  GetComponentLocation() + FVector(CirclePosition.X, 0.0f, CirclePosition.Y);
}