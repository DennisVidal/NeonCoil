// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR
	#define SCREEN_LOG(Text, Color, Duration) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Text)
	#define SCREEN_LOG_TAGGED(Text, Color, Duration) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FString::Printf(TEXT("%s: %s"), *FString(__FUNCTION__), Text))
	#define SCREEN_LOG_FUNC(Color, Duration) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, Duration, Color, *FString(__FUNCTION__))
	#define DEBUG_LOG(Format, ...) UE_LOG(LogTemp, Warning, Format, ##__VA_ARGS__)
#else
	#define SCREEN_LOG(Text, Color, Duration)
	#define SCREEN_LOG_TAGGED(Text, Color, Duration)
	#define SCREEN_LOG_FUNC(Color, Duration) 
	#define DEBUG_LOG(Format, ...)
#endif