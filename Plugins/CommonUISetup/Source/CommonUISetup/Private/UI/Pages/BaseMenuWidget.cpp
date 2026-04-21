// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/BaseMenuWidget.h"
#include "Input/UIActionBindingHandle.h"
#include "CommonActivatableWidgetSwitcher.h"
#include "UI/MainMenu/SettingsMenuSelector.h"
#include "UI/Pages/Settings/OptionsPanel.h"

UBaseMenuWidget::UBaseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetIsFocusable(true);
	SetConsumePointerInput(true);
}

void UBaseMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
}

void UBaseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (AllPagesSet())
	{
		// Settings Tab Buttons 
		WM_Settings->OnAudioPressed.BindDynamic(this, &ThisClass::OnAudioOptionsPressed); 
		WM_Settings->OnVideoPressed.BindDynamic(this, &ThisClass::OnVideoOptionsPressed);
		WM_Settings->OnDisplayPressed.BindDynamic(this, &ThisClass::OnDisplayOptionsPressed);
		WM_Settings->OnBackPressed.BindDynamic(this, &ThisClass::BackToMainMenuPressed); 
	
		// Audio Options button
		WM_AudioOptions->OnBackPressed.BindDynamic(this, &ThisClass::BackToSettingsPressed);
		
		// Video Options button
		WM_VideoOptions->OnBackPressed.BindDynamic(this, &ThisClass::BackToSettingsPressed);
		
		// controls Options button 
		WM_DisplayOptions->OnBackPressed.BindDynamic(this, &ThisClass::BackToSettingsPressed);
	}
}


void UBaseMenuWidget::ChangeWidgetPanel(UCommonActivatableWidgetSwitcher* Switcher, UWidget* InWidget)
{
	if (Switcher && InWidget)
	{
		Switcher->SetActiveWidget(InWidget); 

		if (UCommonActivatableWidget* AW = Cast <UCommonActivatableWidget>(InWidget))
		{
			Switcher->OnActiveWidgetIndexChanged.AddLambda([AW](UWidget* ActiveWidget, int32 ActiveIndex)
			{
				AW->SetFocus(); 
			}); 
		}
	}
}

TOptional<FUIInputConfig> UBaseMenuWidget::GetDesiredInputConfig() const
{
	FUIInputConfig config = FUIInputConfig(ECommonInputMode::Menu,EMouseCaptureMode::CapturePermanently,false);
	config.bIgnoreLookInput = true;
	config.bIgnoreMoveInput = true;
	return config;
}

void UBaseMenuWidget::OnSettingsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_Settings);
}

void UBaseMenuWidget::OnAudioOptionsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_AudioOptions);
}

void UBaseMenuWidget::OnVideoOptionsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_VideoOptions);
}

void UBaseMenuWidget::OnDisplayOptionsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_DisplayOptions);
}

void UBaseMenuWidget::BackToSettingsPressed()
{
	ChangeWidgetPanel(WS_MainMenu, WM_Settings);
}



