// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnAreaComponent.generated.h"


UCLASS(Abstract, Meta = (BlueprintSpawnableComponent))
class SNAKESHOOTER_API USpawnAreaComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	USpawnAreaComponent();

public:
	UFUNCTION(BlueprintCallable)
	virtual FVector GetSpawnPoint() const;


protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
};