// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilityComponent.h"
#include "Abilities/Ability.h"
#include "Interfaces/AbilityOwnerInterface.h"


bool UAbilityComponent::TryActivateAbility() 
{
	return Ability && Ability->TryActivate();
}

bool UAbilityComponent::TryDeactivateAbility() 
{
	return Ability && Ability->TryDeactivate();
}

void UAbilityComponent::OnAbilityActivated(UAbility* InAbility)
{
	OnAbilityActivatedDelegate.Broadcast(InAbility);
}

void UAbilityComponent::OnAbilityDeactivated(UAbility* InAbility)
{
	OnAbilityDeactivatedDelegate.Broadcast(InAbility);
}

void UAbilityComponent::OnAbilityUsed(UAbility* InAbility, float InUsagePercentage)
{
	if (IAbilityOwnerInterface* AbilityOwnerInterface = Cast<IAbilityOwnerInterface>(GetOwner()))
	{
		AbilityOwnerInterface->OnAbilityUsed(InAbility, InUsagePercentage);
	}
}

void UAbilityComponent::GetAbilityLocationAndRotation(FVector& OutLocation, FRotator& OutRotation) const
{
	if(AActor* Owner = GetOwner())
	{
		if (IAbilityOwnerInterface* AbilityOwnerInterface = Cast<IAbilityOwnerInterface>(Owner))
		{
			AbilityOwnerInterface->GetAbilityLocationAndRotation(OutLocation, OutRotation);
			return;
		}

		OutLocation = Owner->GetActorLocation();
		OutRotation = Owner->GetActorRotation();
		return;
	}

	OutLocation = FVector::ZeroVector;
	OutRotation = FRotator::ZeroRotator;
}

void UAbilityComponent::GrantAbility(TSubclassOf<UAbility> InAbilityClass)
{
	if(!InAbilityClass)
	{
		return;
	}
	
	Ability = NewObject<UAbility>(this, InAbilityClass);
	Ability->SetAbilityComponent(this);
	if (IAbilityOwnerInterface* AbilityOwnerInterface = Cast<IAbilityOwnerInterface>(GetOwner()))
	{
		AbilityOwnerInterface->SetAbilityColor(Ability->GetColor());
	}
}

UAbility* UAbilityComponent::GetAbility() const
{
	return Ability;
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	GrantAbility(AbilityClass);
}

