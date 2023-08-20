// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/ScoreInterface.h"
#include "SnakeShooterGameState.generated.h"

/**
 * 
 */
UCLASS()
class SNAKESHOOTER_API ASnakeShooterGameState : public AGameStateBase, public IScoreInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Score = 0;

public:
	virtual int32 GetScore() const override
	{
		return Score;
	}

	virtual void SetScore(int32 InScore) override
	{
		Score = InScore;
	}
};
