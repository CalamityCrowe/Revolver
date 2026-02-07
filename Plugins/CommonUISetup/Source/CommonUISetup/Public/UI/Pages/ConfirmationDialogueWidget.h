// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ConfirmationDialogueWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnConfirmationSelection, bool, Confirm); 

class UBackgroundBlur;
class UBaseMenuButton;
class UHorizontalBox;
class UVerticalBox;
class UCommonTextBlock;
class UCommonBorder; 
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UConfirmationDialogueWidget : public UCommonUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UConfirmationDialogueWidget();
	
	
	
	void ShowDialogueMessage(const FText& Message);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	
	FOnConfirmationSelection ConfirmSelection;
	
protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonBorder> CB_Background;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VB_MessageBox; 
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_Message; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HB_SelectionBox;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> CA_FadeIn; 
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Confirm; 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Cancel; 
	
private: 
	
	void OnConfirmClicked(); 
	
	void OnCancelClicked();
	
};
