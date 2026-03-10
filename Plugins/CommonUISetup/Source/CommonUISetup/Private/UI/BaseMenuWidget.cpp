// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseMenuWidget.h"
#include "Input/UIActionBindingHandle.h"
#include "CommonActivatableWidgetSwitcher.h"

UBaseMenuWidget::UBaseMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UBaseMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	
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
	UE_LOG(LogTemp, Warning, TEXT("GetDesiredInputConfig called!"));

	FUIInputConfig config = FUIInputConfig(ECommonInputMode::Menu,EMouseCaptureMode::CapturePermanently,false);
	config.bIgnoreLookInput = true;
	config.bIgnoreMoveInput = true;
	return config;
}

