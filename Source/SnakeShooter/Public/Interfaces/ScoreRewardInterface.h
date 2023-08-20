// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScoreRewardInterface.generated.h"

UINTERFACE(MinimalAPI)
class UScoreRewardInterface : public UInterface
{
	GENERATED_BODY()
};


class SNAKESHOOTER_API IScoreRewardInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetScoreReward() const = 0;
};
