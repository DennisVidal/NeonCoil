// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ItemInterface.h"
#include "Item.generated.h"

UCLASS()
class SNAKESHOOTER_API AItem : public AActor, public IItemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPaperSpriteComponent> SpriteComponent;

public:	
	AItem();

public:
	virtual void Pickup(AActor* CollectingActor) override;
};
