// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MenuFiles/SaveSettingsFiles.h"
#include "UserSettings.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUISETUP_API UUserSettings : public USaveGame
{
	GENERATED_BODY()
public: 
	UUserSettings(); 
	
	UPROPERTY()
	FAudioOptionsSettings AudioOptions;
};
