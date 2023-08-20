// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakePart.h"
#include "Entities/SnakeShooterPawn.h"
#include "Interfaces/HealthInterface.h"
#include "Interfaces/ItemInterface.h" 
#include "Containers/Deque.h" 
#include "Snake.generated.h"

USTRUCT()
struct SNAKESHOOTER_API FSnakePath
{
	GENERATED_BODY()

public:
	TDeque<FVector> PathPoints;

	UPROPERTY(EditAnywhere)
	float SampleDistance = 32.0f;

	void UpdatePathPoints(const FVector& InTargetPosition);

	void AddPointFirst(const FVector& InPoint);
	void AddPointFirst(const FVector& InPoint, int32 InCount);
	void AddPointLast(const FVector& InPoint);
	void AddPointLast(const FVector& InPoint, int32 InCount);

	void RemovePointFirst();
	void RemovePointFirst(int32 InCount);
	void RemovePointLast();
	void RemovePointLast(int32 InCount);
	
	const FVector& GetFirstPoint() const;
	const FVector& GetLastPoint() const;

	FVector GetPositionAlongPath(float InDistance);

	void DebugDraw(UWorld* InWorld) const;
};



UCLASS()
class SNAKESHOOTER_API ASnake : public ASnakeShooterPawn, public IHealthInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SprintSpeed = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsSprinting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed = 30.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TargetPosition;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class ASnakePart>> Parts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ASnakePart> InitialPartClass;

protected:
	//Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* ActivateAbilityAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* SprintAction;

protected:
	UPROPERTY(EditAnywhere)
	FSnakePath SnakePath;
	
public:
	UPROPERTY()
	FOnDeathDelegate OnDeathDelegate;


public:
	ASnake();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


public:
	void SetTargetPosition(const FVector& InTargetPosition);
	
	UFUNCTION(BlueprintCallable)
	void SetSprintEnabled(bool bEnabled);
	
	UFUNCTION(BlueprintCallable)
	ASnakePart* CreatePart(TSubclassOf<ASnakePart> InSegmentClass);
	
	UFUNCTION(BlueprintCallable)
	int32 AddPart(ASnakePart* InPart);
	
	UFUNCTION(BlueprintCallable)
	void DestroyPart(int32 InPartIndex);
	
	UFUNCTION(BlueprintCallable)
	ASnakePart* RemovePart(int32 InPartIndex);

	void UpdateSnakeParts();

	UFUNCTION(BlueprintCallable)
	void ActivatePrimaryAbility(const struct FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void DeactivatePrimaryAbility(const struct FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	ASnakePart* GetHeadPart() const;

public:
	UFUNCTION()
	void OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor);

public:
	virtual bool DealDamage(float InDamage, AActor* InDamagingActor) override;
	virtual void Kill(AActor* InKillingActor) override;
	virtual FOnDeathDelegate& GetOnDeathDelegate() override;


protected:
	UFUNCTION()
	void OnHeadAbilityDeactivated(UAbility* InAbility);
	
	void OnHeadPartChanged(ASnakePart* NewHead, ASnakePart* OldHead);

};

