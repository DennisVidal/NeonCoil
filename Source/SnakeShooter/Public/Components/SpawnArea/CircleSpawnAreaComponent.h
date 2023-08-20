// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpawnArea/SpawnAreaComponent.h"
#include "CircleSpawnAreaComponent.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class SNAKESHOOTER_API UCircleSpawnAreaComponent : public USpawnAreaComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	bool bAllowSpawningWithinCircle = false;

	UPROPERTY(EditAnywhere)
	float CircleRadius = 100.0f;

public:
	virtual FVector GetSpawnPoint() const override;
};