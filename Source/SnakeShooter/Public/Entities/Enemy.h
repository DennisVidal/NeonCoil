// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entities/SnakeShooterPawn.h"
#include "Interfaces/HealthInterface.h"
#include "Interfaces/ScoreRewardInterface.h"
#include "Enemy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeathDelegate, AEnemy*, InEnemy);

UCLASS()
class SNAKESHOOTER_API AEnemy : public ASnakeShooterPawn, public IHealthInterface, public IScoreRewardInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere)
	float CurrentHealth = 100.0f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 30.0f;

	UPROPERTY(EditAnywhere)
	float FallSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	int32 ScoreReward = 50;
	
public:
	UPROPERTY()
	FOnDeathDelegate OnDeathDelegate;

public:	
	AEnemy();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath(AActor* InKilledActor, AActor* InKiller);

public:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual bool DealDamage(float InDamage, AActor* InDamagingActor) override;
	virtual void Kill(AActor* InKillingActor) override;
	virtual FOnDeathDelegate& GetOnDeathDelegate() override;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetScoreReward() const override;
};
