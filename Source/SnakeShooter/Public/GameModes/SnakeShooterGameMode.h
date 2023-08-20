// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/ObjectiveManagerInterface.h"
#include "SnakeShooterGameMode.generated.h"

UCLASS()
class SNAKESHOOTER_API ASnakeShooterGameMode : public AGameModeBase, public IObjectiveManagerInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Instanced)
	TObjectPtr<class UActorDirector> EnemyDirector;
	UPROPERTY(EditAnywhere, Instanced)
	TObjectPtr<class UActorDirector> ItemDirector;


protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<class USnakeShooterObjective>> Objectives;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UScoreUIWidget> ScoreUIWidget;


protected:
	virtual void BeginPlay() override;

public:
	virtual void PreInitializeComponents() override;

public:
	void RestartLevel();

public:
	UFUNCTION(BlueprintCallable)
	class UActorDirector* GetEnemyDirector() const;
	UFUNCTION(BlueprintCallable)
	class UActorDirector* GetItemDirector() const;

	UFUNCTION(BlueprintCallable)
	void TriggerGameOver();

protected:
	UFUNCTION()
	void OnPlayerDeath(AActor* InKilledPlayer, AActor* InKiller); 

	UFUNCTION()
	void OnObjectiveCompleted(class USnakeShooterObjective* InObjective);

	UFUNCTION()
	void OnObjectiveFailed(class USnakeShooterObjective* InObjective);

protected:
	UFUNCTION()
	void OnEnemySpawned(AActor* InEnemy);
	UFUNCTION()
	void OnEnemyDeath(AActor* InKilledEnemy, AActor* InKiller);


public:
	UFUNCTION(BlueprintCallable)
	virtual void AddObjective(class USnakeShooterObjective* InObjective) override;
};
