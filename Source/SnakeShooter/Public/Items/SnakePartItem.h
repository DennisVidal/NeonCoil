// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "SnakePartItem.generated.h"

/**
 * 
 */
UCLASS()
class SNAKESHOOTER_API ASnakePartItem : public AItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASnakePart> SnakePartClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> SplatterEffect;
	
public:
	virtual void Pickup(AActor* CollectingActor) override;
};
