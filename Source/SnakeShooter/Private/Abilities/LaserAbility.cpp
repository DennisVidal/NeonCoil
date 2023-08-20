// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LaserAbility.h"

#include "SnakeShooterHelpers.h"
#include "Components/AbilityComponent.h"
#include "Entities/Laser.h"


void ULaserAbility::StartFiring()
{
	if(!Laser)
	{
		Laser = CreateLaser();
	}

	Laser->SetEnabled(true);
}

void ULaserAbility::StopFiring()
{
	if(Laser)
	{
		Laser->SetEnabled(false);
	}
}

void ULaserAbility::OnLaserUsed(ALaser* InLaser)
{
	float Percentage = GetUsePercentage();
	if(AbilityComponent)
	{
		AbilityComponent->OnAbilityUsed(this, Percentage);
	}

	if(Percentage <= 0.f)
	{
		Deactivate();
	}
}

ALaser* ULaserAbility::CreateLaser()
{
	FVector Location;
	FRotator Rotation;
	AbilityComponent->GetAbilityLocationAndRotation(Location, Rotation);
	
	ALaser* CreatedLaser = GetWorld()->SpawnActor<ALaser>(LaserClass, Location, Rotation);

	CreatedLaser->AttachToActor(AbilityComponent->GetOwner(), FAttachmentTransformRules::KeepWorldTransform);

	FLaserParameters LaserParams;
	LaserParams.MaxDistance = MaxLaserLength;
	LaserParams.InitialEnergy = InitialEnergy;
	LaserParams.LaserColor = GetColor();
	LaserParams.DamagePerSecond = Damage;
	LaserParams.EnergyUsePerSecond = EnergyUsePerSecond;

	CreatedLaser->SetLaserParameters(LaserParams);

	CreatedLaser->OnLaserUsed.BindDynamic(this, &ULaserAbility::OnLaserUsed);
	
	return CreatedLaser;
}

bool ULaserAbility::HasUsesLeft() const
{
	return !Laser || (Laser->GetEnergy01() > 0.f);
}

float ULaserAbility::GetUsePercentage() const
{
	return Laser ? Laser->GetEnergy01() : 1.f;
}

void ULaserAbility::BeginDestroy()
{
	Super::BeginDestroy();
	if(Laser)
	{
		Laser->Destroy();
	}
}

void ULaserAbility::OnActivate()
{
	StartFiring();
}

void ULaserAbility::OnDeactivate()
{
	StopFiring();
}
