// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/SnakePart.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "SnakeShooterHelpers.h"
#include "Components/AbilityComponent.h"
#include "Entities/Snake.h"

ASnakePart::ASnakePart()
{
	PrimaryActorTick.bCanEverTick = false;
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SetRootComponent(SpriteComponent);

	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("Ability Component"));
	AbilityComponent->SetupAttachment(SpriteComponent);
}

void ASnakePart::BeginPlay()
{
	Super::BeginPlay();
	SpriteMaterialDynamic = SpriteComponent->CreateDynamicMaterialInstance(0);
}

void ASnakePart::SetSnake(ASnake* InSnake)
{
	Snake = InSnake;
}

ASnake* ASnakePart::GetSnake() const
{
	return Snake;
}

float ASnakePart::GetPartRadius() const
{
	//FVector2D SpriteSize = SpriteComponent->GetSprite()->GetSourceSize(); //Works only in editor builds
	int32 SpriteSizeY = SpriteComponent->GetSprite()->GetBakedTexture()->GetSizeY();
	FVector ComponentScale = SpriteComponent->GetComponentScale();
	return 0.5 * SpriteSizeY * ComponentScale.X;
}

FVector ASnakePart::GetPartTailEnd() const
{
	return GetActorLocation() + -GetActorForwardVector() * GetPartRadius();
};

void ASnakePart::UpdateAbilityPercentage(float InPercentage)
{
	if(SpriteMaterialDynamic)
	{
		SpriteMaterialDynamic->SetScalarParameterValue(TEXT("Percentage"), InPercentage);
	}
}

bool ASnakePart::DealDamage(float InDamage, AActor* InDamagingActor)
{
	return Snake && Snake->DealDamage(InDamage, InDamagingActor);
}

void ASnakePart::Kill(AActor* InKillingActor)
{
	if (Snake)
	{
		Snake->Kill(InKillingActor);
	}
}

FOnDeathDelegate& ASnakePart::GetOnDeathDelegate()
{
	return Snake->GetOnDeathDelegate();
}

void ASnakePart::OnAbilityUsed(UAbility* InAbility, float InUsagePercentage)
{
	UpdateAbilityPercentage(InUsagePercentage);
}

void ASnakePart::SetAbilityColor(const FLinearColor& InColor)
{
	if(SpriteComponent)
	{
		SpriteComponent->SetSpriteColor(InColor);
	}
}

void ASnakePart::GetAbilityLocationAndRotation(FVector& OutLocation, FRotator& OutRotation) const
{
	if(SpriteComponent)
	{
		OutLocation = SpriteComponent->GetSocketLocation(TEXT("Ability"));
		OutRotation = SpriteComponent->GetSocketRotation(TEXT("Ability"));
		return;
	}
	
	OutLocation = GetActorLocation();
	OutRotation = GetActorRotation();
}

void ASnakePart::SetFollowTarget(AActor* InFollowTarget, double InFollowDistance)
{
	FollowTarget = InFollowTarget;
	LastTargetPosition = FollowTarget->GetActorLocation();
	SecondToLastTargetPosition = LastTargetPosition;
	FollowDistance = InFollowDistance;
}

void ASnakePart::UpdatePosition(double DeltaTime)
{
	if (!FollowTarget)
	{
		return;
	}

	FVector TargetLocation = FollowTarget->GetActorLocation();
	double DistanceToTarget = FVector::Distance(LastTargetPosition, TargetLocation);
	if (DistanceToTarget > FollowDistance)
	{
		SecondToLastTargetPosition = LastTargetPosition;
		LastTargetPosition += (TargetLocation - LastTargetPosition).GetSafeNormal() * FollowDistance;
		DistanceToTarget -= FollowDistance;
	}

	
	SetActorLocation(FMath::Lerp(SecondToLastTargetPosition, LastTargetPosition, DistanceToTarget / FollowDistance));
	
	FVector ToTarget = (TargetLocation - GetActorLocation()).GetSafeNormal();
	SetActorRotation(FRotator(FMath::RadiansToDegrees(FMath::Atan2(ToTarget.Z, ToTarget.X)), 0, 0));
	
}

UAbilityComponent* ASnakePart::GetAbilityComponent() const
{
	return AbilityComponent;
}
