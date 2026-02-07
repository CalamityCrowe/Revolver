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
	WB_Settings->OnClicked().AddUObject(this, &UMainMenuSelector::OnSettingsButtonPressed); 
	WB_Quit->OnClicked().AddUObject(this, &UMainMenuSelector::OnQuitButtonPressed);
}

UWidget* UMainMenuSelector::NativeGetDesiredFocusTarget() const
{
	
//
	return Super::NativeGetDesiredFocusTarget();
	
	
}

FReply UMainMenuSelector::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	const UCommonInputSubsystem* InputSubsystem = GetInputSubsystem(); 
	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (TSharedPtr<SWidget> PrimarySlateWidget = MenuSelector->GetCachedWidget())
		{
			if (UBaseMenuButton* button = Cast<UBaseMenuButton> (MenuSelector->GetChildAt(0)))
			{
				button->SetFocus(); 
				button->SetIsSelected(true);
				return FReply::Handled();
			}
		}
	}
	
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
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
