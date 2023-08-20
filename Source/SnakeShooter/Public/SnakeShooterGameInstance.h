// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SnakeShooterGameInstance.generated.h"

enum class EGameModeType : uint8;

UCLASS()
class SNAKESHOOTER_API USnakeShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USnakeShooterSaveGame> SaveGame;

public:
	virtual void Init() override;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetHighscore() const;
	UFUNCTION(BlueprintCallable)
	void SetHighscore(int32 InScore);
};
