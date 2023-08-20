// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeShooterSaveGame.h"

int32 USnakeShooterSaveGame::GetHighscore() const
{
	return Highscore;
}

void USnakeShooterSaveGame::SetHighscore(int32 InScore)
{
	Highscore = InScore;
}
