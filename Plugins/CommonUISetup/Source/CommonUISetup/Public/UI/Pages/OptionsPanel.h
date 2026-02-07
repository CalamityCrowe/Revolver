// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MenuDelegates.h"
#include "OptionsPanel.generated.h"


/**
 * 
 */

class UBaseMenuButton;
class UCommonBorder; 
class UCommonTextBlock;
class UHorizontalBox;
class UScrollBox; 
class USizeBox; 
class UVerticalBox;


UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UOptionsPanel : public UCommonUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UOptionsPanel(); 
	
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	FOnButtonPressed OnBackPressed; 
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> WB_SizeBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VB_Selection;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> SB_OptionsScroll;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_MenuText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonBorder> CB_SettingsBorder;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonBorder> CB_ButtonsBorder;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HB_ButtonSelection;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Reset; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Apply; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Back; 
	
	
	UPROPERTY(EditAnywhere)
	FText MenuTextLabel;
	
private: 
	void OnBackButtonPressed(); 
};
