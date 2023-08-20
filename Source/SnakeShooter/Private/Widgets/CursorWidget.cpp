// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CursorWidget.h"
#include "Components/Image.h"

void UCursorWidget::SetCursorColor(const FLinearColor& InColor)
{
	CursorImage->SetColorAndOpacity(InColor);
}

const FLinearColor& UCursorWidget::GetCursorColor() const
{
	return CursorImage->GetColorAndOpacity();
}
