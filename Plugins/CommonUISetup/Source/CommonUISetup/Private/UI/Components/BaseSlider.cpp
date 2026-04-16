// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/BaseSlider.h"

#include "CommonTextBlock.h"
#include "Components/Slider.h"
#include "Kismet/KismetMathLibrary.h"

UBaseSlider::UBaseSlider(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), 
OptionLabelText(FText::FromString("Slider Option")), 
FillMaterialParameter("Percent"),
DefaultValue(0.5),
InputMinRange(0),
InputMaxRange(100)
{
	
}

void UBaseSlider::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CT_OptionText)
	{
		CT_OptionText->SetText(OptionLabelText); 
	}
	if (S_SliderSetting)
	{
		S_SliderSetting->OnValueChanged.RemoveDynamic(this, &UBaseSlider::UpdateValue);
		S_SliderSetting->OnValueChanged.AddDynamic(this, &ThisClass::UpdateValue); 
	}
	if (DM_SliderFill)
	{
		UpdateValue(DefaultValue);
	}
}

void UBaseSlider::InitializeSlider(FText OptionName, float InValue)
{
	DefaultValue = InValue;
	OptionLabelText = OptionName; 
	SetupSliderMaterial(); 
}

float UBaseSlider::GetSliderValue() const
{
	return S_SliderSetting->GetValue();
}

void UBaseSlider::SetupSliderMaterial()
{
	if (MI_SliderMaterial)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Purple, "FUCK YOU VOLUME"); 
		
		DM_SliderFill = UMaterialInstanceDynamic::Create(MI_SliderMaterial,this);
		
		if (!DM_SliderFill)
		{
			return; 
		}
		
		FSliderStyle SliderStyle = S_SliderSetting->GetWidgetStyle();
		SliderStyle.NormalBarImage.SetResourceObject(DM_SliderFill);
		SliderStyle.HoveredBarImage.SetResourceObject(DM_SliderFill);
		SliderStyle.DisabledBarImage.SetResourceObject(DM_SliderFill);
		
		S_SliderSetting->SetWidgetStyle(SliderStyle);
		
		DM_SliderFill->SetScalarParameterValue("Max Percent", S_SliderSetting->GetMaxValue()); 
		S_SliderSetting->SetValue(DefaultValue); 
		if (CT_SliderValue)
		{
			CT_SliderValue->SetText(FText::AsNumber(FMath::RoundToInt(DefaultValue))); 
		}
		
	}
	
}

void UBaseSlider::UpdateValue(float NewValue)
{
	if (!CT_SliderValue || !S_SliderSetting || !DM_SliderFill)
	{
		return;
	}
		float ClampedValue = FMath::GetMappedRangeValueClamped(
	 FVector2D(S_SliderSetting->GetMinValue(), S_SliderSetting->GetMaxValue()),
	FVector2D(InputMinRange, InputMaxRange),
	NewValue);
		DM_SliderFill->SetScalarParameterValue(FillMaterialParameter, NewValue);
		FNumberFormattingOptions Format;
		Format.MaximumFractionalDigits = 0; 
		Format.MinimumIntegralDigits = 2; 
		
		CT_SliderValue->SetText(FText::AsNumber(ClampedValue, &Format)); 
	
}
