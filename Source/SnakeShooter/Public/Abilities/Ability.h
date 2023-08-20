// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

class UAbilityComponent;

UCLASS(Abstract, Blueprintable)
class SNAKESHOOTER_API UAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	bool bIsActive = false;

	UPROPERTY()
	TObjectPtr<UAbilityComponent> AbilityComponent;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor Color;

public:
	UFUNCTION(BlueprintCallable)
	bool IsActive() const;

	UFUNCTION(BlueprintCallable)
	bool TryActivate();

	UFUNCTION(BlueprintCallable)
	bool TryDeactivate();

	UFUNCTION(BlueprintCallable)
	void ForceDeactivate();

	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbilityComponent() const;

	UFUNCTION(BlueprintCallable)
	void SetAbilityComponent(UAbilityComponent* InAbilityComponent);

	UFUNCTION(BlueprintCallable)
	FLinearColor GetColor() const;

	UFUNCTION(BlueprintCallable)
	virtual bool CanActivate() const;

	UFUNCTION(BlueprintCallable)
	virtual bool CanDeactivate() const;

	UFUNCTION(BlueprintCallable)
	virtual bool HasUsesLeft() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetUsePercentage() const;



protected:
	void Activate();
	void Deactivate();

	virtual void OnActivate();
	virtual void OnDeactivate();

public:
	virtual void BeginDestroy() override;
};