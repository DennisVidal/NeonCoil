// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class SNAKESHOOTER_API IItemInterface
{
	GENERATED_BODY()

public:
	virtual void Pickup(AActor* InCollectingActor) = 0;
};
