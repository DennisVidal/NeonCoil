// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/EnemyTarget.h"
#include "Interfaces/ObjectiveManagerInterface.h"
#include "Objectives/SnakeShooterObjective.h"
#include "GameFramework/GameModeBase.h"
#include "NiagaraComponent.h"

AEnemyTarget::AEnemyTarget()
{
	PrimaryActorTick.bCanEverTick = false;
}

float AEnemyTarget::GetHealth01() const
{
	return CurrentHealth / MaxHealth;
}

void AEnemyTarget::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}


void AEnemyTarget::OnDamaged_Implementation(float InDamage, AActor* InDamagingActor)
{
}

bool AEnemyTarget::DealDamage(float InDamage, AActor* InDamagingActor)
{
	if (IHealthInterface* DamagingActorHealthInterface = Cast<IHealthInterface>(InDamagingActor))
	{
		DamagingActorHealthInterface->Kill(this);
	}

	CurrentHealth -= InDamage;
	OnDamaged(InDamage, InDamagingActor);

	if (CurrentHealth <= 0.0f)
	{
		Kill(InDamagingActor);
	}
	return true;
}

void AEnemyTarget::Kill(AActor* InKillingActor)
{
	OnDeathDelegate.Broadcast(this, InKillingActor);
	Destroy();
}

FOnDeathDelegate& AEnemyTarget::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

