// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HealthInterface.h"
#include "EnemyTarget.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SNAKESHOOTER_API AEnemyTarget : public AActor, public IHealthInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 1.0f;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeathDelegate;


public:	
	AEnemyTarget();

	UFUNCTION(BlueprintCallable)
	float GetHealth01() const;

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnDamaged(float InDamage, AActor* InDamagingActor);

public:
	virtual bool DealDamage(float InDamage, AActor* InDamagingActor) override;
	virtual void Kill(AActor* InKillingActor) override;
	virtual FOnDeathDelegate& GetOnDeathDelegate() override;
};
