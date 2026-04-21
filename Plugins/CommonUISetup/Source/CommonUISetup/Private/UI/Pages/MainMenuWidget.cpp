// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/MainMenuWidget.h"

// engine
#include "CommonActivatableWidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

// Common UI Setup Plugin
#include "Components/VerticalBox.h"
#include "UI/MainMenu/MainMenuSelector.h"
#include "UI/MainMenu/SettingsMenuSelector.h"
#include "UI/Pages/Settings/OptionsPanel.h"
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
		WM_MainMenu->OnNewGamePressed.BindDynamic(this, &ThisClass::OnNewGamePressed); 
		WM_MainMenu->OnSettingsPressed.BindDynamic(this, &ThisClass::OnSettingsPressed); 
		WM_MainMenu->OnQuitPressed.BindDynamic(this, &ThisClass::OnQuitPressed);
	}
	
	ActivateWidget(); 
}


void UMainMenuWidget::OnNewGamePressed()
{
	
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
