// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/MainMenuWidget.h"

// engine
#include "CommonActivatableWidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBox.h"
#include "GameFramework/HUD.h"

// Common UI Setup Plugin

#include "Interfaces/HUDInterface.h"
#include "UI/MainMenu/MainMenuSelector.h"
#include "UI/MainMenu/SettingsMenuSelector.h"
#include "UI/Pages/Settings/OptionsPanel.h"
#include "UI/Pages/ConfirmationDialogueWidget.h"
#include "UI/Pages/CreditsWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (AllPagesSet())
	{ 
		// main menu buttons
		WM_MainMenu->OnNewGamePressed.BindDynamic(this, &ThisClass::OnNewGamePressed); 
		WM_MainMenu->OnSettingsPressed.BindDynamic(this, &ThisClass::OnSettingsPressed); 
		WM_MainMenu->OnCreditsPressed.BindDynamic(this, &ThisClass::OnCreditsPressed); 
		WM_Credits->OnCreditsFinished.BindDynamic(this, &ThisClass::CreditsFinished); 
		WM_MainMenu->OnQuitPressed.BindDynamic(this, &ThisClass::OnQuitPressed);
	}
	
	ActivateWidget(); 
}


void UMainMenuWidget::OnNewGamePressed()
{
	
}

void UMainMenuWidget::OnCreditsPressed()
{
	if (ShowCreditsAnim)
	{
		PlayAnimation(ShowCreditsAnim); 
		WM_Credits->ActivateWidget(); 
	}
}

void UMainMenuWidget::CreditsFinished()
{
	if (ShowCreditsAnim)
	{
		PlayAnimationReverse(ShowCreditsAnim);
	}
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

void UMainMenuWidget::BackToMainMenuPressed()
{
	Super::BackToMainMenuPressed();
	ChangeWidgetPanel(WS_MainMenu, WM_MainMenu);
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
