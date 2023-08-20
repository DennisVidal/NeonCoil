// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameModes/SnakeShooterGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnRestartButtonClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnQuitButtonClicked);
	}
}

void UGameOverWidget::OnRestartButtonClicked()
{
	if (ASnakeShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ASnakeShooterGameMode>())
	{
		GameMode->RestartLevel();
	}
}

void UGameOverWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Type::Quit, false);
}

void UGameOverWidget::SetHighscore(int32 InHighscore)
{
	if (HighscoreValueText)
	{
		HighscoreValueText->SetText(FText::AsNumber(InHighscore));
	}
}

void UGameOverWidget::SetScore(int32 InScore)
{
	if (ScoreValueText)
	{
		ScoreValueText->SetText(FText::AsNumber(InScore));
	}
}
