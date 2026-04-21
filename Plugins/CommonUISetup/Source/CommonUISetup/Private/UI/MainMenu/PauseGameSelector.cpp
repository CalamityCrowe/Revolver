// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/PauseGameSelector.h"

#include "UI/Components/BaseMenuButton.h"

void UPauseGameSelector::NativeConstruct()
{
	Super::NativeConstruct();
	WB_ResumeGame->OnClicked().AddUObject(this,&UPauseGameSelector::OnResumeGameButtonPressed); 
	WB_Settings->OnClicked().AddUObject(this,&UPauseGameSelector::OnSettingsButtonPressed);
	WB_MainMenu->OnClicked().AddUObject(this,&UPauseGameSelector::OnMainMenuButtonPressed);
}

void UPauseGameSelector::OnResumeGameButtonPressed() const
{
	if (OnResumePressed.IsBound())
	{
		OnResumePressed.Execute();
	}
}

void UPauseGameSelector::OnSettingsButtonPressed() const
{
	if (OnSettingsPressed.IsBound())
	{
		OnSettingsPressed.Execute();
	}
}

void UPauseGameSelector::OnMainMenuButtonPressed() const
{
	if (OnMainMenuPressed.IsBound())
	{
		OnMainMenuPressed.Execute();
	}
}
