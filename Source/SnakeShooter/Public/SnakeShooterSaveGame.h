// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SnakeShooterSaveGame.generated.h"


UCLASS()
class SNAKESHOOTER_API USnakeShooterSaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Highscore = 0;

public:
	int32 GetHighscore() const;
	void SetHighscore(int32 InScore);
};
