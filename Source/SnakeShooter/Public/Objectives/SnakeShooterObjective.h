// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/HealthInterface.h"
#include "SnakeShooterObjective.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSnakeShooterObjectiveDelegate, USnakeShooterObjective*, InObjective);



UCLASS(EditInlineNew, DefaultToInstanced)
class SNAKESHOOTER_API USnakeShooterObjective : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	bool bIsEnabled = false;

	UPROPERTY(EditAnywhere)
	bool bFailTriggersGameOver = true;

public:
	UPROPERTY()
	FSnakeShooterObjectiveDelegate OnObjectiveCompletedDelegate;
	UPROPERTY()
	FSnakeShooterObjectiveDelegate OnObjectiveFailedDelegate;

public:
	UFUNCTION(BlueprintCallable)
	void EnableObjective();

	UFUNCTION(BlueprintCallable)
	void DisableObjective();

	UFUNCTION(BlueprintCallable)
	bool TriggersGameOverOnFail() const;

	UFUNCTION(BlueprintCallable)
	void CompleteObjective();

	UFUNCTION(BlueprintCallable)
	void FailObjective();

protected:
	virtual bool SetupObjective();
	virtual void OnObjectiveCompleted();
	virtual void OnObjectiveFailed();
};


UCLASS()
class SNAKESHOOTER_API UKeepAliveObjective : public USnakeShooterObjective
{
	GENERATED_BODY()
		
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> TargetActor;


protected:
	virtual bool SetupObjective() override;


	UFUNCTION()
	void OnTargetActorDied(AActor* InTargetActor, AActor* InKiller);

public:
	void SetTargetActor(AActor* InTargetActor);
};