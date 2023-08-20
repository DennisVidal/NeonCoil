// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FLaserDelegate, ALaser*, InLaser);

class UNiagaraComponent;

USTRUCT(BlueprintType)
struct FLaserParameters
{
	GENERATED_BODY()
	
	float MaxDistance = 1000.f;
	float DamagePerSecond = 100.f;
	float InitialEnergy = 10.f;
	float EnergyUsePerSecond = 1.f;
	FLinearColor LaserColor = FLinearColor::Red;
};

UCLASS()
class SNAKESHOOTER_API ALaser : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FLaserDelegate OnLaserUsed;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> LaserEffect;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor LaserColor = FColor::Red;

	UPROPERTY(EditDefaultsOnly)
	float MaxDistance = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float DamagePerSecond = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float InitialEnergy = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float EnergyUsePerSecond = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	float RemainingEnergy = 1.0f;
	
public:	
	// Sets default values for this actor's properties
	ALaser();

	UFUNCTION(BlueprintCallable)
	void SetLaserParameters(const FLaserParameters& Params);
	
	UFUNCTION(BlueprintCallable)
	void SetDamagePerSecond(float InDamagePerSecond);

	UFUNCTION(BlueprintCallable)
	void SetInitialEnergy(float InEnergy);

	UFUNCTION(BlueprintCallable)
	void SetEnergyUsage(float InEnergyUsePerSecond);

	UFUNCTION(BlueprintCallable)
	void SetMaxDistance(float InMaxDistance);

	UFUNCTION(BlueprintCallable)
	void SetLaserColor(const FLinearColor& InLaserColor);

	UFUNCTION(BlueprintCallable)
	void SetEnabled(bool bEnabled);


	UFUNCTION(BlueprintCallable)
	float GetDamagePerSecond() const;

	UFUNCTION(BlueprintCallable)
	float GetInitialEnergy() const;

	UFUNCTION(BlueprintCallable)
	float GetEnergyUsage() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxDistance() const;

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetLaserColor() const;


	UFUNCTION(BlueprintCallable)
	float GetEnergy01() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

