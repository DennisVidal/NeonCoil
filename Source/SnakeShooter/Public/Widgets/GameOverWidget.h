// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class SNAKESHOOTER_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UButton> RestartButton;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> HighscoreValueText;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> ScoreValueText;


protected:
	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
	virtual void OnRestartButtonClicked();
	UFUNCTION()
	virtual void OnQuitButtonClicked();

public:
	void SetHighscore(int32 InHighscore);
	void SetScore(int32 InScore);
};
