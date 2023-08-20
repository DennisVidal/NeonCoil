// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Projectile.h"

#include "PaperSpriteComponent.h"
#include "Engine/GameEngine.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/HealthInterface.h"


// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	InitialLifeSpan = 5.0f;
	
	if(!SpriteComponent)
	{
		SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	}

	SetRootComponent(SpriteComponent);
	SpriteComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	}

	ProjectileMovementComponent->SetUpdatedComponent(SpriteComponent);
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	ProjectileMovementComponent->MaxSpeed = 500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void AProjectile::Fire(const FVector& InDirection)
{
	ProjectileMovementComponent->Velocity = InDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::SetColor(const FLinearColor& InColor)
{
	if(SpriteComponent)
	{
		SpriteComponent->SetSpriteColor(InColor);
	}
}

void AProjectile::SetDamage(float InDamage)
{
	Damage = InDamage;
}

FLinearColor AProjectile::GetColor() const
{
	return SpriteComponent ? SpriteComponent->GetSpriteColor() : FLinearColor::White;
}

float AProjectile::GetDamage() const
{
	return Damage;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IHealthInterface* HealthInterface = Cast<IHealthInterface>(OtherActor))
	{
		HealthInterface->DealDamage(Damage, this);
	}
	
	Destroy();
}
