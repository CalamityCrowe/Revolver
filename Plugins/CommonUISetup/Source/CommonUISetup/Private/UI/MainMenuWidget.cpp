// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"

#include "CommonActivatableWidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Components/BaseMenuButton.h"
#include "UI/MainMenu/MainMenuSelector.h"
#include "UI/MainMenu/SettingsMenuSelector.h"
#include "UI/Pages/ConfirmationDialogueWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	if (UMainMenuSelector* MainMenu = Cast<UMainMenuSelector>(WM_MainMenu))
	{
		MainMenu->GetSettingsButton()->OnClicked().AddUObject(this, &ThisClass::OnSettingsPressed); 
		MainMenu->GetQuitButton()->OnClicked().AddUObject(this, &ThisClass::OnQuitPressed);
	}
	
	if (USettingsMenuSelector* Settings = Cast <USettingsMenuSelector>(WM_Settings))
	{
//		Settings->GetBackButton()->OnClicked().AddUObject()
		//->OnClicked().AddUObject(this, &ThisClass::OnSettingsPressed);
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
