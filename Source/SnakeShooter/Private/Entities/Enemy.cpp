// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Enemy.h"
#include "PaperSpriteComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	SpriteComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpriteComponent->AddLocalRotation(FRotator(DeltaTime * RotationSpeed, 0.0, 0.0));
	AddActorWorldOffset(FVector(0.0, 0.0, DeltaTime * -FallSpeed));
}

void AEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IHealthInterface* HealthInterface = Cast<IHealthInterface>(OtherActor))
	{
		HealthInterface->DealDamage(Damage, this);
	}
}

bool AEnemy::DealDamage(float InDamage, AActor* InDamagingActor)
{
	CurrentHealth -= InDamage;
	if (CurrentHealth <= 0.0f)
	{
		Kill(InDamagingActor);
	}
	return true;
}

void AEnemy::Kill(AActor* InKillingActor)
{
	OnDeath(this, InKillingActor);
	OnDeathDelegate.Broadcast(this, InKillingActor);
	Destroy();
}

FOnDeathDelegate& AEnemy::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

int32 AEnemy::GetScoreReward() const
{
	return ScoreReward;
}
