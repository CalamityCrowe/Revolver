// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveSettingsFiles.generated.h"

USTRUCT(BlueprintType)
struct FAudioOptionsSettings
{
	GENERATED_BODY()
public: 
	UPROPERTY()
	TMap<FName, float> VolumeData;
};

