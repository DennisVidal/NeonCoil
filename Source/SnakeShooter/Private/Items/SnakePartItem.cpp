// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SnakePartItem.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PaperSpriteComponent.h"
#include "Entities/Snake.h"

void ASnakePartItem::Pickup(AActor* CollectingActor)
{
	if (ASnake* Snake = Cast<ASnake>(CollectingActor))
	{
		Snake->CreatePart(SnakePartClass);
	}

	if(SplatterEffect)
	{
		UNiagaraComponent* Splatter = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),SplatterEffect,	GetActorLocation(),	GetActorRotation());
		Splatter->SetBoolParameter(FName("UseCircle"), true);
		Splatter->SetColorParameter(FName("Color"), SpriteComponent->GetSpriteColor());
		Splatter->SetFloatParameter(FName("Velocity"), 300.f);
	}
	
	Destroy();
}
