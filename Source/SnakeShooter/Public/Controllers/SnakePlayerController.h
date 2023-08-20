// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePlayerController.generated.h"

enum class EInputMappingContextPriorities 
{
	GAMEPLAY,
	UI
};

class UInputMappingContext;

UCLASS()
class SNAKESHOOTER_API ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UCursorWidget> CrosshairWidgetClass;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCursorWidget> CrosshairWidget;

protected:
	//Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> GeneralInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> PauseAction;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UPauseWidget> PauseWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanTogglePause = true;

public:
	ASnakePlayerController();
	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:
	UFUNCTION(BlueprintCallable)
	void TogglePause();

	UFUNCTION(BlueprintCallable)
	void ShowPauseWidget(bool bShow);


	UFUNCTION(BlueprintCallable)
	void SetCanTogglePause(bool bInCanTogglePause);

	UFUNCTION(BlueprintCallable)
	bool CanTogglePause() const;

public:
	UFUNCTION(BlueprintCallable)
	void SetCrosshairColor(const FLinearColor& InColor);

public:
	UFUNCTION(BlueprintCallable)
	void AddInputMappingContext(UInputMappingContext* InInputMappingContext, int32 InPriority);

	UFUNCTION(BlueprintCallable)
	void RemoveInputMappingContext(UInputMappingContext* InInputMappingContext);

public:
	UFUNCTION(BlueprintCallable)
	void UpdateTargetPosition();
};
