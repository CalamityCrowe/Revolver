// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/UserSettingsSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "SaveGame/UserSettings.h"

UUserSettingsSubsystem::UUserSettingsSubsystem():SG_UserSettings(nullptr), SaveFileName("GameOptions")
{
}

void UUserSettingsSubsystem::SaveAudioSettings(FAudioOptionsSettings inAudioSettings)
{
	if (SG_UserSettings)
	{
		SG_UserSettings->AudioOptions = inAudioSettings;
		SaveSettings();
	}
}


UUserSettings* UUserSettingsSubsystem::LoadSettings()
{
	if (IsValid(SG_UserSettings))
	{
		return SG_UserSettings; 
	}
	else
	{
		if (UGameplayStatics::DoesSaveGameExist(SaveFileName, 0))
		{
			return SG_UserSettings = Cast<UUserSettings>(UGameplayStatics::LoadGameFromSlot(SaveFileName, 0)); 
		}
		else
		{
			return SG_UserSettings = Cast<UUserSettings>(UGameplayStatics::CreateSaveGameObject(UUserSettings::StaticClass())); 
		}
	}
	return nullptr;
}

void UUserSettingsSubsystem::SaveSettings()
{
	if (SG_UserSettings)
	{
		UGameplayStatics::SaveGameToSlot(SG_UserSettings,SaveFileName,0); 
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green,"Saving Settings Worked"); 
	}
}
