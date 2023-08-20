// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectiveManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectiveManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SNAKESHOOTER_API IObjectiveManagerInterface
{
	GENERATED_BODY()

public:
	virtual void AddObjective(class USnakeShooterObjective* InObjective) = 0;
};
