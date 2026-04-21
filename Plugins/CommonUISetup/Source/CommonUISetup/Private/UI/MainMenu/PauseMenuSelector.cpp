// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/PauseMenuSelector.h"

#include "UI/Components/BaseMenuButton.h"


UPauseMenuSelector::UPauseMenuSelector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UPauseMenuSelector::NativeConstruct()
{
	Super::NativeConstruct();
	WB_ResumeGame->OnClicked().AddUObject(this,&UPauseMenuSelector::OnResumeGameButtonPressed); 
	WB_Settings->OnClicked().AddUObject(this,&UPauseMenuSelector::OnSettingsButtonPressed);
	WB_MainMenu->OnClicked().AddUObject(this,&UPauseMenuSelector::OnMainMenuButtonPressed);
}

void UPauseMenuSelector::OnResumeGameButtonPressed() const
{
	if (OnResumePressed.IsBound())
	{
		OnResumePressed.Execute();
	}
}

void UPauseMenuSelector::OnSettingsButtonPressed() const
{
	if (OnSettingsPressed.IsBound())
	{
		OnSettingsPressed.Execute();
	}
}

void UPauseMenuSelector::OnMainMenuButtonPressed() const
{
	if (OnMainMenuPressed.IsBound())
	{
		OnMainMenuPressed.Execute();
	}
}
