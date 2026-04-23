// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/Settings/AudioPanel.h"

#include "AudioMixerBlueprintLibrary.h"
#include "Components/ScrollBox.h"
#include "Data/AudioSettingsTable.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/UserSettings.h"
#include "Subsystem/UserSettingsSubsystem.h"
#include "UI/Components/BaseSlider.h"
#include "UI/Components/OptionsCycler.h"
#include "UI/Components/Audio/CustomAudioSlider.h"

UAudioPanel::UAudioPanel(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	MenuTextLabel = FText::FromString("Audio Options"); 	
}


void UAudioPanel::InitializeOptions()
{
	Super::InitializeOptions(); 
	
	// we clear all the audio options here so we dont double up on the UI when it is reoppened 
	VolumeSliders.Empty();
	AudioDeviceCycler = nullptr; 
	InitalizeSliders();
	
	// we create an event to indicate all the found audio devices has been found
	FOnAudioOutputDevicesObtained DevicesObtainedDelegate;
	DevicesObtainedDelegate.BindDynamic(this, &UAudioPanel::OnAudioDevicesObtained); 
	UAudioMixerBlueprintLibrary::GetAvailableAudioOutputDevices(GetWorld(),DevicesObtainedDelegate); 
}

void UAudioPanel::InitalizeSliders()
{
	// we create a copy of the audio settings stored in the subsystems save settings
	FAudioOptionsSettings VolumeData; 
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UUserSettingsSubsystem* UserSettingsSubsystem =  GI->GetSubsystem<UUserSettingsSubsystem>())
		{
			if (UUserSettings* Settings = UserSettingsSubsystem->LoadSettings())
				VolumeData = Settings->AudioOptions;
		}
	}
	// we check if the data table, the slider class and scroll box is valid here as we dont want to continue otherwise
	if (OptionsTable && SliderWidgetClass && SB_OptionsScroll)
	{
		// standard getting all the names of the data table rows and looping through them
		TArray<FName> RowNames = OptionsTable->GetRowNames();
		for (FName RowName : RowNames)
		{
			// we atytempt to find the setting we are looking for and validate it here
			FAudioConfig* RowData = OptionsTable->FindRow<FAudioConfig>(RowName, TEXT("")); 
			if (RowData)
			{
				if (UCustomAudioSlider* AS = CreateWidget<UCustomAudioSlider>(this, SliderWidgetClass))
				{
					const float* FoundVolume = VolumeData.VolumeData.Find(RowName); // we grab the volume value from the volume datas map
					float Volume = FoundVolume ? *FoundVolume : RowData->DefaultVolume;   // we then ckeck if it found one and decide if we should use the DT value or save value
					
					// the standard initiallization stuff
					AS->InitializeSlider(RowData->SoundClassName, Volume); 
					AS->InitializeSoundSettings(RowData->SoundClass, RowData->SoundClassMix); 
					AS->SetPadding(OptionsPadding);
					VolumeSliders.Add(RowName,AS); 
					
					SB_OptionsScroll->AddChild(AS); 
				}
				
			}
		}
		
		
	}
}

void UAudioPanel::OnAudioDevicesObtained(const TArray<FAudioOutputDeviceInfo>& AvailableDevices)
{
	TArray<FText> AudioDevicesText;
	int ActiveAudioDevice = 0;
	FText OptionText = FText::FromString("Audio Device");
	
	// we grab a copy of the audio devices it found when the delgate fires
	AudioDevices = AvailableDevices; 
	for (int i = 0; i < AudioDevices.Num(); ++i) // we loop through each of the devices one by one to add name of them to be used in the cycler
	{
		AudioDevicesText.Add(FText::FromString(AudioDevices[i].Name)); 
		if (AudioDevices[i].bIsCurrentDevice || AudioDevices[i].bIsSystemDefault) // we check if it is either the current or default device and if so, that is assigned as the active index
		{
			ActiveAudioDevice = i;
		}
	}
	
	// from here it is the standard create widget and bind delegates/initialize
	AudioDeviceCycler = CreateWidget<UOptionsCycler>(this, OptionsCycleClass); 
	if (AudioDeviceCycler && SB_OptionsScroll)
	{
		AudioDeviceCycler->InitializeOption(OptionText,AudioDevicesText,ActiveAudioDevice);
		AudioDeviceCycler->SetPadding(OptionsPadding);
		AudioDeviceCycler->OnOptionsChanged.AddDynamic(this,&UAudioPanel::OnAudioDeviceChanged); 
		
		SB_OptionsScroll->AddChild(AudioDeviceCycler);
	}
}

void UAudioPanel::OnAudioDeviceChanged(int SelectedIndex)
{
	// we check if the audio device we are selecting is valid before we change it 
	if (!AudioDevices.IsValidIndex(SelectedIndex))
	{
		return;
	}

	
	// we pull the device ID and validate it as well, to ensure it doesn't crash or fail
	// away
	const FString& DeviceId = AudioDevices[SelectedIndex].DeviceId;
	if (DeviceId.IsEmpty())
	{
		return;
	}
	
	// we unbind the delegate first before rebinding it
	if (DeviceSwapDelegate.IsBound())
	{
		DeviceSwapDelegate.Unbind();
	}
	DeviceSwapDelegate.BindDynamic(this, &UAudioPanel::OnDeviceSwapCompleted);
	
	// we call the function to swap the actual device and return the result if it succeeded or not
	UAudioMixerBlueprintLibrary::SwapAudioOutputDevice(
		GetWorld(),
		DeviceId,
		DeviceSwapDelegate
	);
}

void UAudioPanel::OnDeviceSwapCompleted(const FSwapAudioOutputResult& SwapResult)
{
	if (SwapResult.Result == ESwapAudioOutputDeviceResultState::Success)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, 
			FString::Printf(TEXT("Audio device swapped to: %s"), *SwapResult.RequestedDeviceId));
	}
	else if (SwapResult.Result == ESwapAudioOutputDeviceResultState::Failure)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 		
			FString::Printf(TEXT("Audio device failed to swap: %s"), *SwapResult.RequestedDeviceId));
	}
}

void UAudioPanel::ApplyOptions()
{
	Super::ApplyOptions();
	// we grab the subsystem here to make sure that it is valid before attempting to save the settings
	if (UUserSettingsSubsystem* UserSettingsSubsystem =  GetGameInstance()->GetSubsystem<UUserSettingsSubsystem>())
	{
		FAudioOptionsSettings VolumeData; 
		
		for (TPair<FName, UCustomAudioSlider*> VolumeSlider : VolumeSliders)
		{
			VolumeData.VolumeData.Add(VolumeSlider.Key, VolumeSlider.Value->GetSliderValue()); 
		}
		UserSettingsSubsystem->SaveAudioSettings(VolumeData);
	} 
}

void UAudioPanel::ResetOptions()
{
	TArray<FName> RowNames = OptionsTable->GetRowNames();
	for (FName RowName : RowNames)
	{
		if (FAudioConfig* RowData = OptionsTable->FindRow<FAudioConfig>(RowName, TEXT("")))
		{
			if (UCustomAudioSlider* OC =  *VolumeSliders.Find(RowName))
			{
				OC->UpdateValue(RowData->DefaultVolume); 
			} 
		}	
	}
}
