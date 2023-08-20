// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AbilityComponent.generated.h"


class UAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityDelegate, UAbility*, InAbility);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNAKESHOOTER_API UAbilityComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FAbilityDelegate OnAbilityActivatedDelegate;

	UPROPERTY()
	FAbilityDelegate OnAbilityDeactivatedDelegate;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAbility> AbilityClass;

	UPROPERTY()
	TObjectPtr<UAbility> Ability;
	
public:
	UFUNCTION(BlueprintCallable)
	bool TryActivateAbility();

	UFUNCTION(BlueprintCallable)
	bool TryDeactivateAbility();


	UFUNCTION(BlueprintCallable)
	void GetAbilityLocationAndRotation(FVector& OutLocation, FRotator& OutRotation) const;

	UFUNCTION(BlueprintCallable)
	void GrantAbility(TSubclassOf<UAbility> InAbilityClass);

	UFUNCTION(BlueprintCallable)
	UAbility* GetAbility() const;

	void OnAbilityActivated(UAbility* InAbility);
	void OnAbilityDeactivated(UAbility* InAbility);
	void OnAbilityUsed(UAbility* InAbility, float InUsagePercentage);

protected:
	virtual void BeginPlay() override;
};
