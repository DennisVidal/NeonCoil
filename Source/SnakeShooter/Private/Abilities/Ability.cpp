// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Ability.h"
#include "Components/AbilityComponent.h"

bool UAbility::IsActive() const
{
	return bIsActive;
}


bool UAbility::TryActivate()
{
	if(CanActivate())
	{
		Activate();
		return true;
	}

	return false;
}

bool UAbility::TryDeactivate()
{
	if(CanDeactivate())
	{
		Deactivate();
		return true;
	}

	return false;
}

void UAbility::ForceDeactivate()
{
	Deactivate();
}

UAbilityComponent* UAbility::GetAbilityComponent() const
{
	return AbilityComponent;
}

void UAbility::SetAbilityComponent(UAbilityComponent* InAbilityComponent)
{
	AbilityComponent = InAbilityComponent;
}

FLinearColor UAbility::GetColor() const
{
	return Color;
}

bool UAbility::CanActivate() const
{
	return !IsActive() && HasUsesLeft();
}

bool UAbility::CanDeactivate() const
{
	return IsActive();
}

bool UAbility::HasUsesLeft() const
{
	return true;
}

float UAbility::GetUsePercentage() const
{
	return 1.0f;
}

void UAbility::Activate()
{
	bIsActive = true;	
	if(AbilityComponent)
	{
		AbilityComponent->OnAbilityActivated(this);
	}
	
	OnActivate();
}

void UAbility::Deactivate()
{
	bIsActive = false;
	OnDeactivate();
	
	if(AbilityComponent)
	{
		AbilityComponent->OnAbilityDeactivated(this);
	}
}

void UAbility::OnActivate()
{
	Deactivate();
}

void UAbility::OnDeactivate()
{

}

void UAbility::BeginDestroy()
{
	Super::BeginDestroy();
	Deactivate();
}
