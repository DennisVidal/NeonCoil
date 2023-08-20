// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ScoreUIWidget.h"
#include "Components/TextBlock.h"

void UScoreUIWidget::SetScore(int32 InScore)
{
	ScoreValueText->SetText(FText::AsNumber(InScore));
}
