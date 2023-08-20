// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Laser.h"
#include "NiagaraComponent.h"
#include "SnakeShooterHelpers.h"
#include "Interfaces/HealthInterface.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	LaserEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Laser Effect"));
	LaserEffect->SetupAttachment(RootComponent);
}

void ALaser::SetLaserParameters(const FLaserParameters& Params)
{
	SetInitialEnergy(Params.InitialEnergy);
	SetEnergyUsage(Params.EnergyUsePerSecond);
	SetDamagePerSecond(Params.DamagePerSecond);
	SetMaxDistance(Params.MaxDistance);
	SetLaserColor(Params.LaserColor);
}

void ALaser::SetInitialEnergy(float InEnergy)
{
	InitialEnergy = InEnergy;
	RemainingEnergy = InitialEnergy;
}

void ALaser::SetEnergyUsage(float InEnergyUsePerSecond)
{
	EnergyUsePerSecond = InEnergyUsePerSecond;
}

void ALaser::SetDamagePerSecond(float InDamagePerSecond)
{
	DamagePerSecond = InDamagePerSecond;
}

void ALaser::SetMaxDistance(float InMaxDistance)
{
	MaxDistance = InMaxDistance;
}

void ALaser::SetLaserColor(const FLinearColor& InLaserColor)
{
	LaserColor = InLaserColor;
	LaserEffect->SetColorParameter(FName("Color"), LaserColor);
}

void ALaser::SetEnabled(bool bEnabled)
{
	SetActorHiddenInGame(!bEnabled);
	SetActorEnableCollision(bEnabled);
	SetActorTickEnabled(bEnabled);

	if(LaserEffect)
	{
		bEnabled ? LaserEffect->Activate(true) : LaserEffect->Deactivate();
	}
}



float ALaser::GetDamagePerSecond() const
{
	return DamagePerSecond;
}

float ALaser::GetInitialEnergy() const
{
	return InitialEnergy;
}

float ALaser::GetEnergyUsage() const
{
	return EnergyUsePerSecond;
}

float ALaser::GetMaxDistance() const
{
	return MaxDistance;
}

const FLinearColor& ALaser::GetLaserColor() const
{
	return LaserColor;
}

void ALaser::BeginPlay()
{
	Super::BeginPlay();
	LaserEffect->SetColorParameter(FName("Color"), LaserColor);
}

void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector StartPosition = GetActorLocation();
	FVector EndPositon = StartPosition + GetActorForwardVector() * MaxDistance;
	
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPositon, ECollisionChannel::ECC_WorldDynamic);
	if(bHit)
	{
		EndPositon = HitResult.Location;

		if (IHealthInterface* HealthInterface = Cast<IHealthInterface>(HitResult.GetActor()))
		{
			HealthInterface->DealDamage(DamagePerSecond * DeltaTime, this);
		}
	}
	
	LaserEffect->SetVectorParameter(FName("HitPosition"), EndPositon);

	RemainingEnergy -= EnergyUsePerSecond * DeltaTime;
	OnLaserUsed.ExecuteIfBound(this);
	if(RemainingEnergy <= 0.0f)
	{
		SetEnabled(false);
	}
}

float ALaser::GetEnergy01() const
{
	return RemainingEnergy / InitialEnergy;
}

