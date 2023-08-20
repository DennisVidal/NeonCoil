// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScoreInterface.generated.h"

UINTERFACE(MinimalAPI)
class UScoreInterface : public UInterface
{
	GENERATED_BODY()
};

class SNAKESHOOTER_API IScoreInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetScore() const = 0;
	virtual void SetScore(int32 InScore) = 0;
	void AddScore(int32 InScore)
	{
		SetScore(GetScore() + InScore);
	};
};
