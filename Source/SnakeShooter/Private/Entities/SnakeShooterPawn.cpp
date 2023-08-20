// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/SnakeShooterPawn.h"
#include "PaperSpriteComponent.h"

ASnakeShooterPawn::ASnakeShooterPawn()
{
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(FName("Sprite"));
	RootComponent = SpriteComponent;
}

