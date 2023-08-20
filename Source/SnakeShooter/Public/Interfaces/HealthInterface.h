// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeathDelegate, AActor*, InKilledActor, AActor*, InKiller);


UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};


class SNAKESHOOTER_API IHealthInterface
{
	GENERATED_BODY()

public:
	virtual bool DealDamage(float InDamage, AActor* InDamagingActor) = 0;
	virtual void Kill(AActor* InKillingActor) = 0;

	virtual FOnDeathDelegate& GetOnDeathDelegate() = 0;
};
