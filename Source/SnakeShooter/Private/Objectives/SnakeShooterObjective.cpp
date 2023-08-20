// Fill out your copyright notice in the Description page of Project Settings.


#include "Objectives/SnakeShooterObjective.h"

void USnakeShooterObjective::EnableObjective()
{
	bIsEnabled = SetupObjective();
}

void USnakeShooterObjective::DisableObjective()
{
	bIsEnabled = false;
}

bool USnakeShooterObjective::TriggersGameOverOnFail() const
{
	return bFailTriggersGameOver;
}

void USnakeShooterObjective::CompleteObjective()
{
	OnObjectiveCompleted();
	OnObjectiveCompletedDelegate.Broadcast(this);
	DisableObjective();
}

void USnakeShooterObjective::FailObjective()
{
	OnObjectiveFailed();
	OnObjectiveFailedDelegate.Broadcast(this);
	DisableObjective();
}

bool USnakeShooterObjective::SetupObjective()
{
	return true;
}

void USnakeShooterObjective::OnObjectiveCompleted()
{
}

void USnakeShooterObjective::OnObjectiveFailed()
{
}

bool UKeepAliveObjective::SetupObjective()
{
	bool bSuccess = Super::SetupObjective();
	if (!bSuccess)
	{
		return false;
	}

	if (IHealthInterface* HealthInterface = Cast<IHealthInterface>(TargetActor))
	{
		HealthInterface->GetOnDeathDelegate().AddDynamic(this, &UKeepAliveObjective::OnTargetActorDied);
		return true;
	}

	return false;
}

void UKeepAliveObjective::OnTargetActorDied(AActor* InTargetActor, AActor* InKiller)
{
	FailObjective();
}

void UKeepAliveObjective::SetTargetActor(AActor* InTargetActor)
{
	TargetActor = InTargetActor;
}
