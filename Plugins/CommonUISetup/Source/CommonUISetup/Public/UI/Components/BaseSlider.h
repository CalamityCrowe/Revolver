// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Internationalization/TextFormatter.h"
#include "BaseSlider.generated.h"

/**
 * 
 */
class UCommonBorder; 
class UHorizontalBox;
class UCommonTextBlock;
class USlider;
class USizeBox;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UOverlay; 

UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UBaseSlider : public UCommonUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	virtual void NativePreConstruct() override;
	
	virtual void InitializeSlider(FText OptionName, float InValue); 
	
	
	
	float GetSliderValue()const;
	
protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonBorder> CB_SliderBorder; 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HB_SliderBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_OptionText;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<USlider> S_SliderSetting;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UOverlay> OV_SliderOverlay;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CT_SliderValue; 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SB_SliderSize;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> MI_SliderMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* DM_SliderFill;
	
	UPROPERTY(EditAnywhere)
	FText OptionLabelText; 
	
	UPROPERTY(EditAnywhere)
	FName FillMaterialParameter; 
	
	UPROPERTY(EditAnywhere)
	float DefaultValue; 
	
	UPROPERTY(EditAnywhere)
	float InputMinRange; 
	
	UPROPERTY(EditAnywhere)
	float InputMaxRange;
	
	UFUNCTION()
	virtual void UpdateValue(float NewValue); 
	
private: 
	
	void SetupSliderMaterial(); 
	

};
