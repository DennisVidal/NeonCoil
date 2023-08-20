// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameModes/SnakeShooterGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeButtonClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPauseWidget::OnRestartButtonClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::OnQuitButtonClicked);
	}
}
void UPauseWidget::OnResumeButtonClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	RemoveFromViewport();
}

void UPauseWidget::OnRestartButtonClicked()
{
	if (ASnakeShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ASnakeShooterGameMode>())
	{
		GameMode->RestartLevel();
	}
}

void UPauseWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Type::Quit, false);
}

void UPauseWidget::SetHighscore(int32 InHighscore)
{
	if (HighscoreValueText)
	{
		HighscoreValueText->SetText(FText::AsNumber(InHighscore));
	}
}

void UPauseWidget::SetScore(int32 InScore)
{
	if (ScoreValueText)
	{
		ScoreValueText->SetText(FText::AsNumber(InScore));
	}
}
