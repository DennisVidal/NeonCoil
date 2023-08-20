// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeShooterGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeShooterSaveGame.h"
#include "Settings/SnakeShooterSettings.h"

void USnakeShooterGameInstance::Init()
{
	Super::Init();

	USaveGame* Save = UGameplayStatics::DoesSaveGameExist(TEXT("Save"), 0) ?
		UGameplayStatics::LoadGameFromSlot(TEXT("Save"), 0)
		: UGameplayStatics::CreateSaveGameObject(GetDefault<USnakeShooterSettings>()->SaveGameClass);

	SaveGame = Cast<USnakeShooterSaveGame>(Save);
}

int32 USnakeShooterGameInstance::GetHighscore() const
{
	return SaveGame->GetHighscore();
}

void USnakeShooterGameInstance::SetHighscore(int32 InScore)
{
	SaveGame->SetHighscore(InScore);
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Save"), 0);
}
