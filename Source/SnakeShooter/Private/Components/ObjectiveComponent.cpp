// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ObjectiveComponent.h"
#include "Interfaces/ObjectiveManagerInterface.h"
#include "Objectives/SnakeShooterObjective.h"
#include "GameFramework/GameModeBase.h"

UObjectiveComponent::UObjectiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UKeepAliveObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (IObjectiveManagerInterface* ObjectiveManager = Cast<IObjectiveManagerInterface>(GameMode))
	{
		UKeepAliveObjective* Objective = NewObject<UKeepAliveObjective>(GameMode);
		Objective->SetTargetActor(GetOwner());
		ObjectiveManager->AddObjective(Objective);
	}
}