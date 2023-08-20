// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpawnArea/SpawnAreaComponent.h"
#include "BoxSpawnAreaComponent.generated.h"

/**
 * 
 */
UCLASS(Meta = (BlueprintSpawnableComponent))
class SNAKESHOOTER_API UBoxSpawnAreaComponent : public USpawnAreaComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget))
		FVector BoxMin = FVector(-200.0, 0.0, -200.0);

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget))
		FVector BoxMax = FVector(200.0, 0.0, 200.0);

public:
	virtual FVector GetSpawnPoint() const override;
};
