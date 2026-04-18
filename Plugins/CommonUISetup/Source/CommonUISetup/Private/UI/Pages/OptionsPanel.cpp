// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/OptionsPanel.h"

#include "CommonTextBlock.h"
#include "Components/ScrollBox.h"
#include "UI/Components/BaseMenuButton.h"

UOptionsPanel::UOptionsPanel(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	SetIsFocusable(true);	
	OptionsPadding = FMargin(0.0f,5.0f);
}

void UOptionsPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CT_MenuText)
	{
		CT_MenuText->SetText(MenuTextLabel); 
	}
	// we call this here so we can see what this looks like in the editor before launching the game
	InitializeOptions();
	
}
// we bind the options back button on clicked event
void UOptionsPanel::NativeConstruct()
{
	Super::NativeConstruct();
	
	WB_Back->OnClicked().AddUObject(this, &UOptionsPanel::OnBackButtonPressed); 
	WB_Apply->OnClicked().AddUObject(this, &UOptionsPanel::ApplyOptions);
	WB_Reset->OnClicked().AddUObject(this, &UOptionsPanel::ResetOptions);
}

void UOptionsPanel::InitializeOptions()
{
	SB_OptionsScroll->ClearChildren(); // emptys the widget
}

void UOptionsPanel::ApplyOptions()
{
	
}

void UOptionsPanel::ResetOptions()
{
	
}

void UOptionsPanel::OnBackButtonPressed()
{
	if (OnBackPressed.IsBound())
	{
		OnBackPressed.Execute();
	}
}
