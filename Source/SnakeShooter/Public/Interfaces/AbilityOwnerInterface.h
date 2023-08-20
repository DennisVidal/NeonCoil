// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilityOwnerInterface.generated.h"

class UAbility;
class UAbilityComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbilityOwnerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SNAKESHOOTER_API IAbilityOwnerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnAbilityUsed(UAbility* InAbility, float InUsagePercentage) = 0;
	
	virtual void SetAbilityColor(const FLinearColor& InColor) = 0;
	
	virtual UAbilityComponent* GetAbilityComponent() const = 0;
	
	virtual void GetAbilityLocationAndRotation(FVector& OutLocation, FRotator& OutRotation) const = 0;
};
