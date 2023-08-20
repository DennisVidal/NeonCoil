// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "PaperSpriteComponent.h"
#include "Interfaces/ItemInterface.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(FName("Sprite"));
	RootComponent = SpriteComponent;
}

void AItem::Pickup(AActor* CollectingActor)
{
	Destroy();
}
