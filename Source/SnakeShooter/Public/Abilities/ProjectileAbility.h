// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/WeaponAbility.h"
#include "ProjectileAbility.generated.h"

class AProjectile;

UCLASS()
class SNAKESHOOTER_API UProjectileAbility : public UWeaponAbility
{
	GENERATED_BODY()

	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileClass;

protected:
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 1))
	int32 InitialAmmoCount = 1;

	UPROPERTY()
	int32 RemainingAmmoCount = 1;
	
	//Firerate in shots per second
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0))
	float FireRate = 1.f;

	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 1))
	int32 ProjectilesPerShot = 1;
	
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0.0f, ClampMax = 360.0f, EditCondition="ProjectilesPerShot > 1", EditConditionHides))
	float ProjectileGroupingAngle = 0.f;

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0.0f, ClampMax = 360.0f))
	float MaxDispersionAngle = 0.f;


public:
	UFUNCTION(BlueprintCallable)
	bool IsFiring() const;
	
protected:
	virtual void Fire();

protected:
	void StartFiring();
	void StopFiring();

	
	AProjectile* FireProjectile(const FVector& ProjectilePosition, const FRotator& ProjectileRotation, const FVector& ProjectileDirection);
	AProjectile* CreateProjectile(const FVector& Position, const FRotator& Rotation);

public:
	virtual bool HasUsesLeft() const override;
	virtual float GetUsePercentage() const override;
	virtual void PostInitProperties() override;

protected:
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;
};
