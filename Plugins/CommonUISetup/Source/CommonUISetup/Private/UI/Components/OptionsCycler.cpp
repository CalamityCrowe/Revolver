// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/OptionsCycler.h"

#include "CommonTextBlock.h"
#include "UI/Components/BaseMenuButton.h"
#include "UI/Components/BaseOptionsRotator.h"

UOptionsCycler::UOptionsCycler(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	OptionLabelText = FText::FromString("Option");
}



void UOptionsCycler::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	WB_NextButton->OnClicked().AddUObject(this,&UOptionsCycler::OnNextButtonClicked); 
	WB_PreviousButton->OnClicked().AddUObject(this,&UOptionsCycler::OnPreviousButtonClicked);
}

void UOptionsCycler::InitializeOption(const FText& CurrentOptionText, const TArray<FText>& CurrentOptionArray,
	const int CurrentDefaultIndex)
{
	OptionLabelText = CurrentOptionText;
	OptionsArray = CurrentOptionArray;
	DefaultSelectedIndex = CurrentDefaultIndex;
	SetupWidgetDisplay();
}
void UOptionsCycler::SetupWidgetDisplay()
{
	CT_OptionName->SetText(OptionLabelText); 
	if (WR_OptionRotator)
	{
		WR_OptionRotator->PopulateTextLabels(OptionsArray); 
		WR_OptionRotator->SetSelectedItem(DefaultSelectedIndex); 
	}
}
void UOptionsCycler::OnPreviousButtonClicked()
{
	WR_OptionRotator->ShiftTextLeft(); 
}

void UOptionsCycler::OnNextButtonClicked()
{
	WR_OptionRotator->ShiftTextRight(); 
}
