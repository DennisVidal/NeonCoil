// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpawnArea/SpawnAreaComponent.h"
#include "LineSpawnAreaComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class SNAKESHOOTER_API ULineSpawnAreaComponent : public USpawnAreaComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget))
		FVector LineStart = FVector(-200.0, 0.0, 0.0);

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget))
		FVector LineEnd = FVector(200.0, 0.0, 0.0);


public:
	virtual FVector GetSpawnPoint() const override;

};
