// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakeShooterPawn.generated.h"

UCLASS()
class SNAKESHOOTER_API ASnakeShooterPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPaperSpriteComponent* SpriteComponent;
	
public:
	ASnakeShooterPawn();
};
