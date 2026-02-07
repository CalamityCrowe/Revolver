// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/BaseMenuSelector.h"
#include "MainMenuSelector.generated.h"

class UBaseMenuButton;
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UMainMenuSelector : public UBaseMenuSelector
{
	GENERATED_UCLASS_BODY()
public: 
	UMainMenuSelector(); 
	
	FOnButtonPressed OnNewGamePressed;
	FOnButtonPressed OnSettingsPressed;
	FOnButtonPressed OnQuitPressed;
	
	virtual void NativeConstruct() override;
	
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
private: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_NewGame;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Settings;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Quit;
	
	void OnNewGameButtonPressed() const;
	void OnSettingsButtonPressed() const;
	void OnQuitButtonPressed() const;
};
