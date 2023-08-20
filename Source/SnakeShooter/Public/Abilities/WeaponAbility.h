// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "WeaponAbility.generated.h"


UCLASS()
class SNAKESHOOTER_API UWeaponAbility : public UAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin = 0))
	float Damage;

public:
	UFUNCTION(BlueprintCallable)
	float GetDamage() const;
};
