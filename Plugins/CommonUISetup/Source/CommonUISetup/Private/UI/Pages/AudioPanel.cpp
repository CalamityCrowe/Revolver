// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/AudioPanel.h"

#include "Components/ScrollBox.h"
#include "Data/AudioSettingsTable.h"
#include "UI/Components/BaseSlider.h"
#include "UI/Components/Audio/CustomAudioSlider.h"

UAudioPanel::UAudioPanel(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	MenuTextLabel = FText::FromString("Audio Options"); 	
}

void UAudioPanel::InitializeOptions()
{
	Super::InitializeOptions(); 
	
	VolumeSliders.Empty();
	
	if (OptionsTable && SliderWidgetClass)
	{
		TArray<FName> RowNames = OptionsTable->GetRowNames();
		for (FName RowName : RowNames)
		{
			FAudioConfig* RowData = OptionsTable->FindRow<FAudioConfig>(RowName, TEXT("")); 
			if (RowData)
			{
				if (UCustomAudioSlider* AS = CreateWidget<UCustomAudioSlider>(GetWorld(), SliderWidgetClass))
				{
					AS->InitializeSlider(RowData->SoundClassName, RowData->DefaultVolume); 
					AS->InitializeSoundSettings(RowData->SoundClass, RowData->SoundClassMix); 
					AS->SetPadding(FMargin(0.f,0.f,0.f,10.f));
					VolumeSliders.Add(RowName,AS); 
					
					SB_OptionsScroll->AddChild(AS); 
				}
				
			}
		}
	}
}

void UAudioPanel::ApplyOptions()
{
	
}

void UAudioPanel::ResetOptions()
{
	
}
