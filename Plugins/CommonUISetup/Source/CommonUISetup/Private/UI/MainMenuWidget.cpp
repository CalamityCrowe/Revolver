// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"

// engine
#include "CommonActivatableWidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

// Common UI Setup Plugin
#include "UI/Components/BaseMenuButton.h"
#include "UI/MainMenu/MainMenuSelector.h"
#include "UI/MainMenu/SettingsMenuSelector.h"
#include "UI/Pages/OptionsPanel.h"
#include "UI/Pages/ConfirmationDialogueWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (AllPagesSet())
	{ 
		// main menu buttons
		WM_MainMenu->OnSettingsPressed.BindDynamic(this, &ThisClass::OnSettingsPressed); 
		WM_MainMenu->OnQuitPressed.BindDynamic(this, &ThisClass::OnQuitPressed);
	
		// Settings Tab Buttons 
		WM_Settings->OnAudioPressed.BindDynamic(this, &ThisClass::OnAudioOptionsPressed); 
		WM_Settings->OnVideoPressed.BindDynamic(this, &ThisClass::OnVideoOptionsPressed);
		WM_Settings->OnControlsPressed.BindDynamic(this, &ThisClass::OnControlsOptionsPressed);
		WM_Settings->OnBackPressed.BindDynamic(this, &ThisClass::BackToMainMenuPressed); 
	
		// Audio Options button
		WM_AudioOptions->OnBackPressed.BindDynamic(this, &ThisClass::BackToSettingsPressed);
		
		// Video Options button
		WM_VideoOptions->OnBackPressed.BindDynamic(this, &ThisClass::BackToSettingsPressed);
		
		// controls Options button 
		WM_ControlsOptions->OnBackPressed.BindDynamic(this, &ThisClass::BackToSettingsPressed);
	}
	
	ActivateWidget(); 
}

void UMainMenuWidget::OnSettingsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_Settings); 
}

void UMainMenuWidget::OnQuitPressed()
{
	if (QuitWidgetClass)
	{
		UConfirmationDialogueWidget* ConfirmationWidget = CreateWidget<UConfirmationDialogueWidget>(GetOwningPlayer(),QuitWidgetClass);
		ConfirmationWidget->ShowDialogueMessage(QuitMessage); 
		
		ConfirmationWidget->ConfirmSelection.BindDynamic(this, &ThisClass::UMainMenuWidget::QuitConfirmation); 
	}
}

void UMainMenuWidget::OnAudioOptionsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_AudioOptions);
}

void UMainMenuWidget::OnVideoOptionsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_VideoOptions);
}

void UMainMenuWidget::OnControlsOptionsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_ControlsOptions);
}

void UMainMenuWidget::BackToMainMenuPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_MainMenu);
}

void UMainMenuWidget::BackToSettingsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_Settings);
}

void UMainMenuWidget::QuitConfirmation(bool Confirm)
{
	if (Confirm)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),GetOwningPlayer(),EQuitPreference::Quit,true); 
	}
	else
	{
		
	}
}
