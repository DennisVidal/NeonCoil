// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/SnakeShooterGameMode.h"
#include "Directors/ActorDirector.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/GameOverWidget.h"
#include "Settings/SnakeShooterSettings.h"
#include "Interfaces/HealthInterface.h"
#include "Interfaces/ScoreInterface.h"
#include "Interfaces/ScoreRewardInterface.h"
#include "Objectives/SnakeShooterObjective.h"
#include "SnakeShooterGameInstance.h"
#include "Controllers/SnakePlayerController.h"
#include "Widgets/ScoreUIWidget.h"

void ASnakeShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!ScoreUIWidget)
	{
		ScoreUIWidget = CreateWidget<UScoreUIWidget>(GetWorld(), GetDefault<USnakeShooterSettings>()->ScoreUIWidgetClass);
		ScoreUIWidget->AddToViewport();
	}
}

void ASnakeShooterGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (EnemyDirector)
	{
		EnemyDirector->OnActorSpawnedDelegate.AddDynamic(this, &ASnakeShooterGameMode::OnEnemySpawned);
		EnemyDirector->Initialize();
		EnemyDirector->StartBehaviours();
	}

	if (ItemDirector)
	{
		ItemDirector->Initialize();
		ItemDirector->StartBehaviours();
	}
}

void ASnakeShooterGameMode::RestartLevel()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GetLevel());
}


UActorDirector* ASnakeShooterGameMode::GetEnemyDirector() const
{
	return EnemyDirector;
}

UActorDirector* ASnakeShooterGameMode::GetItemDirector() const
{
	return ItemDirector;
}

void ASnakeShooterGameMode::TriggerGameOver()
{

	if (ASnakePlayerController* PlayerController = Cast<ASnakePlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->SetCanTogglePause(false);
	}
	UGameplayStatics::SetGamePaused(this, true);

	const USnakeShooterSettings* SnakeShooterSettings = GetDefault<USnakeShooterSettings>();
	UGameOverWidget* GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), SnakeShooterSettings->GameOverWidgetClass);
	GameOverWidget->AddToViewport();

	IScoreInterface* CurrentScoreInterface = GetGameState<IScoreInterface>();
	int32 CurrentScore = CurrentScoreInterface ? CurrentScoreInterface->GetScore() : 0;

	USnakeShooterGameInstance* GameInstance = GetGameInstance<USnakeShooterGameInstance>();
	int32 CurrentHighscore = GameInstance ? GameInstance->GetHighscore() : 0;

	if (CurrentScore > CurrentHighscore)
	{
		if (GameInstance)
		{
			GameInstance->SetHighscore(CurrentScore);
		}
		CurrentHighscore = CurrentScore;
	}

	GameOverWidget->SetScore(CurrentScore);
	GameOverWidget->SetHighscore(CurrentHighscore);
}




void ASnakeShooterGameMode::OnPlayerDeath(AActor* InKilledPlayer, AActor* InKiller)
{
	TriggerGameOver();
}

void ASnakeShooterGameMode::OnObjectiveCompleted(USnakeShooterObjective* InObjective)
{
}

void ASnakeShooterGameMode::OnObjectiveFailed(USnakeShooterObjective* InObjective)
{
	if (InObjective->TriggersGameOverOnFail())
	{
		TriggerGameOver();
	}
}

void ASnakeShooterGameMode::OnEnemySpawned(AActor* InEnemy)
{
	if (IHealthInterface* HealthInterface = Cast<IHealthInterface>(InEnemy))
	{
		HealthInterface->GetOnDeathDelegate().AddDynamic(this, &ASnakeShooterGameMode::OnEnemyDeath);
	}
}

void ASnakeShooterGameMode::OnEnemyDeath(AActor* InKilledEnemy, AActor* InKiller)
{
	if (InKiller == InKilledEnemy)
	{
		return;
	}

	if (IScoreInterface* ScoreInterface = GetGameState<IScoreInterface>())
	{
		if (IScoreRewardInterface* ScoreRewardInterface = Cast<IScoreRewardInterface>(InKilledEnemy))
		{
			ScoreInterface->AddScore(ScoreRewardInterface->GetScoreReward());

			if (ScoreUIWidget)
			{
				ScoreUIWidget->SetScore(ScoreInterface->GetScore());
			}
		}
	}
}

void ASnakeShooterGameMode::AddObjective(USnakeShooterObjective* InObjective)
{
	Objectives.Add(InObjective);
	InObjective->OnObjectiveCompletedDelegate.AddDynamic(this, &ASnakeShooterGameMode::OnObjectiveCompleted);
	InObjective->OnObjectiveFailedDelegate.AddDynamic(this, &ASnakeShooterGameMode::OnObjectiveFailed);
	InObjective->EnableObjective();
}