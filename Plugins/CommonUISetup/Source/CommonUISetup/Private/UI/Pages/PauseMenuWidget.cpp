// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/PauseMenuWidget.h"

#include "UI/MainMenu/PauseMenuSelector.h"

UPauseMenuWidget::UPauseMenuWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (AllPagesSet())
	{
		WM_PauseSelector->OnResumePressed.BindDynamic(this, &ThisClass::OnResumeGamePressed);
		WM_PauseSelector->OnSettingsPressed.BindDynamic(this, &ThisClass::OnSettingsPressed);
		WM_PauseSelector->OnMainMenuPressed.BindDynamic(this, &ThisClass::OnMainMenuPressed);
	}
}

void UPauseMenuWidget::OnResumeGamePressed()
{
	// will implement this later
}

void UPauseMenuWidget::OnMainMenuPressed()
{
	// same as above
}

void UPauseMenuWidget::BackToMainMenuPressed()
{
	Super::BackToMainMenuPressed();
	ChangeWidgetPanel(WS_MainMenu, WM_PauseSelector); 
}


