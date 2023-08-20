// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SnakeShooterSettings.generated.h"

UCLASS(Config = Game, DefaultConfig, Meta = (DisplayName = "Snake Shooter Settings"))
class SNAKESHOOTER_API USnakeShooterSettings : public UDeveloperSettings
{
	GENERATED_BODY()
		
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UGameOverWidget> GameOverWidgetClass;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UPauseWidget> PauseWidgetClass;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UScoreUIWidget> ScoreUIWidgetClass;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Save")
	TSubclassOf<class USnakeShooterSaveGame> SaveGameClass;

};