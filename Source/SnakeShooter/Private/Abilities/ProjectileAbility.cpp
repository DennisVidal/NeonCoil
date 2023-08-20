// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ProjectileAbility.h"

#include "Components/AbilityComponent.h"
#include "Entities/Projectile.h"


bool UProjectileAbility::IsFiring() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(FireRateTimerHandle);
}

void UProjectileAbility::Fire()
{
	checkf(ProjectileClass, TEXT("UProjectileAbility needs to have a valid projectile class set!"));
	
	check(AbilityComponent);
	
	FVector Location;
	FRotator Rotation;
	AbilityComponent->GetAbilityLocationAndRotation(Location, Rotation);

	AActor* AbilityOwner = AbilityComponent->GetOwner();
	
	FVector ProjectilePosition = Location;
	FVector ShotDirection = Rotation.Vector();

	//Calculated direction angle based on max dispersion
	float ShotDirectionAngle =
		FMath::RadiansToDegrees(FMath::Atan2(ShotDirection.Z, ShotDirection.X));

	FRotator ProjectileRotation;

	if(ProjectilesPerShot < 2)
	{
		ProjectileRotation = FRotator(ShotDirectionAngle + FMath::RandRange(-MaxDispersionAngle * 0.5f, MaxDispersionAngle * 0.5f),0.0,0.0);
		FireProjectile(ProjectilePosition, ProjectileRotation, ProjectileRotation.Vector());
	}
	else
	{
		float AngleBetweenProjectiles = ProjectileGroupingAngle / ProjectilesPerShot;
		float HalfProjectileGroupingAngle = ProjectileGroupingAngle * 0.5f;

		for(int32 i = 0; i < ProjectilesPerShot; ++i)
		{
			ProjectileRotation = FRotator(ShotDirectionAngle + HalfProjectileGroupingAngle - (i * AngleBetweenProjectiles + FMath::RandRange(0.f, AngleBetweenProjectiles * 0.5f)),0.0,0.0);
			FireProjectile(ProjectilePosition, ProjectileRotation, ProjectileRotation.Vector());
		}
	}

	RemainingAmmoCount--;
	AbilityComponent->OnAbilityUsed(this, GetUsePercentage());
	
	if(RemainingAmmoCount < 1)
	{
		Deactivate();
	}
}

void UProjectileAbility::StartFiring()
{
	float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(FireRateTimerHandle);
	float InitialDelay = RemainingTime > 0.f ? RemainingTime : 0.f;
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &UProjectileAbility::Fire, 1/FireRate, true, InitialDelay);
}

void UProjectileAbility::StopFiring()
{
	if(const UWorld* World = GetWorld())
	{
		float RemainingTime = World->GetTimerManager().GetTimerRemaining(FireRateTimerHandle);
		
		RemainingTime > 0.f ?
			World->GetTimerManager().SetTimer(FireRateTimerHandle, RemainingTime, false) : World->GetTimerManager().ClearTimer(FireRateTimerHandle);
	}
}

AProjectile* UProjectileAbility::FireProjectile(const FVector& ProjectilePosition, const FRotator& ProjectileRotation, const FVector& ProjectileDirection)
{
	AProjectile* Projectile = CreateProjectile(ProjectilePosition, ProjectileRotation);
	if(Projectile)
	{
		Projectile->Fire(ProjectileDirection);
	}

	return Projectile;
}

AProjectile* UProjectileAbility::CreateProjectile(const FVector& InPosition, const FRotator& InRotation)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = AbilityComponent ? AbilityComponent->GetOwner() : nullptr;
	SpawnParameters.Instigator = SpawnParameters.Owner ? SpawnParameters.Owner->GetInstigator() : nullptr;

	AProjectile* SpawnedProjectile= GetWorld()->SpawnActor<AProjectile>(ProjectileClass, InPosition, InRotation, SpawnParameters);
	if(SpawnedProjectile)
	{
		SpawnedProjectile->SetColor(Color);
		SpawnedProjectile->SetDamage(Damage);
	}
	
	return SpawnedProjectile;
}

bool UProjectileAbility::HasUsesLeft() const
{
	return Super::HasUsesLeft() && (RemainingAmmoCount > 0);
}

float UProjectileAbility::GetUsePercentage() const
{
	return static_cast<float>(RemainingAmmoCount) / InitialAmmoCount;
}

void UProjectileAbility::OnActivate()
{
	StartFiring();
}

void UProjectileAbility::OnDeactivate()
{
	StopFiring();
}

void UProjectileAbility::PostInitProperties()
{
	Super::PostInitProperties();
	RemainingAmmoCount = InitialAmmoCount;
}