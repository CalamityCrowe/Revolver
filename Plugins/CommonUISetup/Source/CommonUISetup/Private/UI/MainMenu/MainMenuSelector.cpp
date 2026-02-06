// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu/MainMenuSelector.h"
#include "CommonInputSubsystem.h"
#include "Components/VerticalBox.h"
#include "UI/Components/BaseMenuButton.h"

UMainMenuSelector::UMainMenuSelector(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	
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
