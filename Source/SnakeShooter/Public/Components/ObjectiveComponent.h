// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SNAKESHOOTER_API UObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObjectiveComponent();
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SNAKESHOOTER_API UKeepAliveObjectiveComponent : public UObjectiveComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
