// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/AbilityOwnerInterface.h"
#include "Interfaces/HealthInterface.h"
#include "SnakePart.generated.h"


UCLASS()
class SNAKESHOOTER_API ASnakePart : public AActor, public IHealthInterface, public IAbilityOwnerInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<class ASnake> Snake;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPaperSpriteComponent> SpriteComponent;
	
	UPROPERTY()
	TObjectPtr<AActor> FollowTarget;
	UPROPERTY()
	FVector LastTargetPosition;
	UPROPERTY()
	FVector SecondToLastTargetPosition;
	UPROPERTY()
	double FollowDistance = 0.0f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAbilityComponent> AbilityComponent;

	UPROPERTY()
	UMaterialInstanceDynamic* SpriteMaterialDynamic;
public:
	ASnakePart();

	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetSnake(class ASnake* InSnake);

	UFUNCTION(BlueprintCallable)
	ASnake* GetSnake() const;

	UFUNCTION(BlueprintCallable)
	float GetPartRadius() const;

	UFUNCTION(BlueprintCallable)
	FVector GetPartTailEnd() const;

	UFUNCTION(BlueprintCallable)
	void UpdateAbilityPercentage(float InPercentage);
	
public:
	virtual bool DealDamage(float InDamage, AActor* InDamagingActor) override;
	virtual void Kill(AActor* InKillingActor) override;
	virtual FOnDeathDelegate& GetOnDeathDelegate() override;


	virtual void OnAbilityUsed(UAbility* InAbility, float InUsagePercentage) override;

	virtual void SetAbilityColor(const FLinearColor& InColor) override;
	
	virtual UAbilityComponent* GetAbilityComponent() const override;
	virtual void GetAbilityLocationAndRotation(FVector& OutLocation, FRotator& OutRotation) const override;

public:
	UFUNCTION(BlueprintCallable)
	void SetFollowTarget(AActor* InFollowTarget, double InFollowDistance);

	UFUNCTION(BlueprintCallable)
	void UpdatePosition(double DeltaTime);
	
};
