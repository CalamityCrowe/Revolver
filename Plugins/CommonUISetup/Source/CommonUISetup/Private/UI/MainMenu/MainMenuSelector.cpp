// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuSelector.h"
#include "CommonInputSubsystem.h"
#include "Components/VerticalBox.h"
#include "UI/Components/BaseMenuButton.h"

UMainMenuSelector::UMainMenuSelector(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	
}

void UMainMenuSelector::NativeConstruct()
{
	Super::NativeConstruct();
	WB_NewGame->OnClicked().AddUObject(this, &UMainMenuSelector::OnNewGameButtonPressed);
	WB_Settings->OnClicked().AddUObject(this, &UMainMenuSelector::OnSettingsButtonPressed); 
	WB_Quit->OnClicked().AddUObject(this, &UMainMenuSelector::OnQuitButtonPressed);
    
	SetFocus();
}

UWidget* UMainMenuSelector::NativeGetDesiredFocusTarget() const
{
	if (UBaseMenuButton* Button = Cast<UBaseMenuButton>(MenuSelector->GetChildAt(0)))
	{
		return Button;
	}
	return Super::NativeGetDesiredFocusTarget();
}

FReply UMainMenuSelector::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMainMenuSelector::OnNewGameButtonPressed() const
{
	if (OnNewGamePressed.IsBound())
	{
		OnNewGamePressed.Execute();
	}
}

void UMainMenuSelector::OnSettingsButtonPressed() const
{
	if (OnSettingsPressed.IsBound())
	{
		OnSettingsPressed.Execute();
	}
}

void UMainMenuSelector::OnQuitButtonPressed() const
{
	if (OnQuitPressed.IsBound())
	{
		OnQuitPressed.Execute();
	}
}
