// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/SettingsMenuSelector.h"

#include "UI/Components/BaseMenuButton.h"

USettingsMenuSelector::USettingsMenuSelector(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void USettingsMenuSelector::NativeConstruct()
{
	Super::NativeConstruct();
	
	WB_Audio->OnClicked().AddUObject(this, &USettingsMenuSelector::OnAudioButtonPressed); 
	WB_Video->OnClicked().AddUObject(this, &USettingsMenuSelector::OnVideoButtonPressed);
	WB_Controls->OnClicked().AddUObject(this, &USettingsMenuSelector::OnControlsButtonPressed);
	WB_Back->OnClicked().AddUObject(this, &USettingsMenuSelector::OnBackButtonPressed);
}

void USettingsMenuSelector::OnAudioButtonPressed()
{
	if (OnAudioPressed.IsBound())
	{
		OnAudioPressed.Execute();
	}
}

void USettingsMenuSelector::OnVideoButtonPressed()
{
	if (OnVideoPressed.IsBound())
	{
		OnVideoPressed.Execute();
	}
}

void USettingsMenuSelector::OnControlsButtonPressed()
{
	if (OnControlsPressed.IsBound())
	{
		OnControlsPressed.Execute();
	}
}

void USettingsMenuSelector::OnBackButtonPressed()
{
	if (OnBackPressed.IsBound())
	{
		OnBackPressed.Execute(); 
	}
}
