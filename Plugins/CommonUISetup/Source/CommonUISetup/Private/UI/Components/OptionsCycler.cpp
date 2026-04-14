// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/OptionsCycler.h"

#include "CommonTextBlock.h"
#include "UI/Components/BaseMenuButton.h"
#include "UI/Components/BaseOptionsRotator.h"

UOptionsCycler::UOptionsCycler(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer), bMarkedAsCustom(false)
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

void UOptionsCycler::UpdateSelection(int NewIndex)
{
	WR_OptionRotator->SetSelectedItem(NewIndex);
	bMarkedAsCustom = false;
}

void UOptionsCycler::MarkAsCustom()
{
	WR_OptionRotator->MarkAsCustom();
	bMarkedAsCustom = true;
}

int32 UOptionsCycler::GetCurrentSetting() const
{
	if (WR_OptionRotator)
	{
		return bMarkedAsCustom == true ?  -1 : WR_OptionRotator->GetSelectedIndex(); // we return -1 for an invalid index
	}
	return DefaultSelectedIndex;
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
	OnOptionsChanged.Broadcast(WR_OptionRotator->GetSelectedIndex()); 
	bMarkedAsCustom = false;
}

void UOptionsCycler::OnNextButtonClicked()
{
	WR_OptionRotator->ShiftTextRight(); 
	OnOptionsChanged.Broadcast(WR_OptionRotator->GetSelectedIndex()); 
	bMarkedAsCustom = false;
}
