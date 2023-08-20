// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CursorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SNAKESHOOTER_API UCursorWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	TObjectPtr<class UImage> CursorImage;

public:
	UFUNCTION(BlueprintCallable)
	void SetCursorColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetCursorColor() const;
};
