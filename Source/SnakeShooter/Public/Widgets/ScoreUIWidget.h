// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class SNAKESHOOTER_API UScoreUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> ScoreValueText;

public:
	UFUNCTION(BlueprintCallable)
	void SetScore(int32 InScore);
};
