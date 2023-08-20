// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/WeaponAbility.h"
#include "LaserAbility.generated.h"

class ALaser;

UCLASS()
class SNAKESHOOTER_API ULaserAbility : public UWeaponAbility
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 1.f))
	float InitialEnergy = 10.f;

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0.f))
	float EnergyUsePerSecond = 1.f;
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 1.f))
	float MaxLaserLength = 100.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALaser> LaserClass;

	UPROPERTY()
	TObjectPtr<ALaser> Laser;

protected:
	void StartFiring();
	void StopFiring();

	UFUNCTION()
	void OnLaserUsed(ALaser* InLaser);
	
	ALaser* CreateLaser();
public:
	virtual bool HasUsesLeft() const override;
	virtual float GetUsePercentage() const override;
	virtual void BeginDestroy() override;

protected:
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
};
