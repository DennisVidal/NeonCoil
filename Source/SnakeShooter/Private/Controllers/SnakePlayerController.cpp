// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SnakePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Entities/Snake.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Widgets/CursorWidget.h"
#include "Widgets/PauseWidget.h"
#include "Settings/SnakeShooterSettings.h"
#include "Interfaces/ScoreInterface.h"
#include "SnakeShooterGameInstance.h"

ASnakePlayerController::ASnakePlayerController()
{
	bShowMouseCursor = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ASnakePlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddInputMappingContext(GeneralInputMappingContext, static_cast<int32>(EInputMappingContextPriorities::UI));

	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UCursorWidget>(this, CrosshairWidgetClass);
		SetMouseCursorWidget(EMouseCursor::Type::Crosshairs, CrosshairWidget);
	}
	
}

void ASnakePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ASnakePlayerController::TogglePause);
	}
}

void ASnakePlayerController::TogglePause()
{
	if (!CanTogglePause()) //Can toggle pause?
	{
		return;
	}
	bool bIsPaused = UGameplayStatics::IsGamePaused(this);

	UGameplayStatics::SetGamePaused(this, !bIsPaused);
	ShowPauseWidget(!bIsPaused);
}

void ASnakePlayerController::ShowPauseWidget(bool bShow)
{
	if (!bShow)
	{
		if (PauseWidget)
		{
			PauseWidget->RemoveFromViewport();
		}
		return;
	}

	if (!PauseWidget)
	{
		PauseWidget = CreateWidget<UPauseWidget>(this, GetDefault<USnakeShooterSettings>()->PauseWidgetClass);
	}

	IScoreInterface* CurrentScoreInterface = GetWorld()->GetGameState<IScoreInterface>();
	PauseWidget->SetScore(CurrentScoreInterface ? CurrentScoreInterface->GetScore() : 0);

	USnakeShooterGameInstance* GameInstance = GetGameInstance<USnakeShooterGameInstance>();
	PauseWidget->SetHighscore(GameInstance ? GameInstance->GetHighscore() : 0);

	PauseWidget->AddToViewport(1);
}

void ASnakePlayerController::SetCanTogglePause(bool bInCanTogglePause)
{
	bCanTogglePause = bInCanTogglePause;
}

bool ASnakePlayerController::CanTogglePause() const
{
	return bCanTogglePause;
}

void ASnakePlayerController::SetCrosshairColor(const FLinearColor& InColor)
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetCursorColor(InColor);
	}
}

void ASnakePlayerController::AddInputMappingContext(UInputMappingContext* InInputMappingContext, int32 InPriority)
{
	if(UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(!InputSubsystem->HasMappingContext(InInputMappingContext))
		{
			InputSubsystem->AddMappingContext(InInputMappingContext, InPriority);
		}
	}
}

void ASnakePlayerController::RemoveInputMappingContext(UInputMappingContext* InInputMappingContext)
{
	if(UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		FModifyContextOptions Options;
		Options.bIgnoreAllPressedKeysUntilRelease = true;
		
		InputSubsystem->RemoveMappingContext(InInputMappingContext, Options);
	}
}


void ASnakePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTargetPosition();
}

void ASnakePlayerController::UpdateTargetPosition()
{
	FVector2D MousePosition;
	if (!GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		return;
	}

	FVector WorldPosition;
	FVector WorldDirection;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, MousePosition, WorldPosition, WorldDirection))
	{
		return;
	}

	if (ASnake* SnakePawn = GetPawn<ASnake>())
	{
		FVector TargetPosition = FMath::RayPlaneIntersection(WorldPosition, WorldDirection, FPlane(FVector(0.0, 1.0, 0.0), 0.0));
		SnakePawn->SetTargetPosition(TargetPosition);
	}
}
