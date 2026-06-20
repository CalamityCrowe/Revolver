// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MenuFIles/SaveSettingsFiles.h"
#include "UserSettingsSubsystem.generated.h"


class UUserSettings;

UCLASS()
class COMMONUISETUP_API UUserSettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public: 
	
	UUserSettingsSubsystem(); 
	
	UFUNCTION()
	void SaveAudioSettings(FAudioOptionsSettings inAudioSettings);
	
	
	UUserSettings* LoadSettings(); 

protected: 
	
	UFUNCTION()
	void SaveSettings(); 
	
	UPROPERTY()
	UUserSettings* SG_UserSettings;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString SaveFileName;
};

