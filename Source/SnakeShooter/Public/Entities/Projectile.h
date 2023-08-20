// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UPaperSpriteComponent;
class UProjectileMovementComponent;

UCLASS()
class SNAKESHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 1.f;
	
public:
	AProjectile();

	UFUNCTION(BlueprintCallable)
	void Fire(const FVector& InDirection);

	UFUNCTION(BlueprintCallable)
	void SetColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	void SetDamage(float InDamage);

	UFUNCTION(BlueprintCallable)
	FLinearColor GetColor() const;

	UFUNCTION(BlueprintCallable)
	float GetDamage() const;
	
protected:
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
