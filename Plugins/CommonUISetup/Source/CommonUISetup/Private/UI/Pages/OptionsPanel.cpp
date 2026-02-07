// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/OptionsPanel.h"

#include "CommonTextBlock.h"
#include "UI/Components/BaseMenuButton.h"

UOptionsPanel::UOptionsPanel(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

void UOptionsPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CT_MenuText)
	{
		CT_MenuText->SetText(MenuTextLabel); 
	}
}

void UOptionsPanel::NativeConstruct()
{
	Super::NativeConstruct();
	
	WB_Back->OnClicked().AddUObject(this, &UOptionsPanel::OnBackButtonPressed); 
}

void UOptionsPanel::OnBackButtonPressed()
{
	if (OnBackPressed.IsBound())
	{
		OnBackPressed.Execute();
	}
}
