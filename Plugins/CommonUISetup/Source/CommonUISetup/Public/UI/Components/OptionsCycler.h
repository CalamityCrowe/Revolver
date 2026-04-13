// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MenuDelegates.h"
#include "OptionsCycler.generated.h"

class UCommonBorder; 
class UCommonTextBlock;
class UBaseOptionsRotator;
class UHorizontalBox;
class UBaseMenuButton; 
/**
 * 
 */
UCLASS()
class COMMONUISETUP_API UOptionsCycler : public UCommonUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	virtual void NativePreConstruct() override;
	
	void InitializeOption(const FText& CurrentOptionText, const TArray<FText>& CurrentOptionArray, int CurrentDefaultIndex);
	
	UPROPERTY(BlueprintAssignable)
	FOnOptionsChanged OnOptionsChanged;
	
	void UpdateSelection(int NewIndex); 
	
	void MarkAsCustom(); 
protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonBorder> CB_OptionBorder; 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HB_OptionBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_OptionName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_PreviousButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseOptionsRotator> WR_OptionRotator;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_NextButton;
	
	UPROPERTY(EditAnywhere)
	FText OptionLabelText; 
	
	UPROPERTY(EditAnywhere)
	TArray<FText> OptionsArray; 
	
	UPROPERTY(EditAnywhere)
	int32 DefaultSelectedIndex;
	
private: 
	void SetupWidgetDisplay();
	void OnPreviousButtonClicked();
	void OnNextButtonClicked();
};
