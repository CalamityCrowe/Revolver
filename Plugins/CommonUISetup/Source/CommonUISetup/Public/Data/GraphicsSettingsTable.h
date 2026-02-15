// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MenuFiles/GraphicsOptions.h"
#include "GraphicsSettingsTable.generated.h"

/**
 * 
 */

USTRUCT()
struct FGraphicsConfig : public FTableRowBase
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere)
	EGraphicsOptions GraphicsOptionType;
	UPROPERTY(EditAnywhere)
	TMap<int, FText> Options;
	UPROPERTY(EditAnywhere)
	int DefaultOption; 
	FGraphicsConfig():GraphicsOptionType(EGraphicsOptions::Overall), DefaultOption(0)
	{
		Options.Add(0, FText::FromString(TEXT("Low")));
		Options.Add(1, FText::FromString(TEXT("Medium")));
		Options.Add(2, FText::FromString(TEXT("High")));
		Options.Add(3, FText::FromString(TEXT("Epic")));
		Options.Add(4, FText::FromString(TEXT("Cinematic")));
	}; 
};

