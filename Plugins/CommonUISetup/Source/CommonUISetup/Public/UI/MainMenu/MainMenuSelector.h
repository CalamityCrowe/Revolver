// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/BaseMenuSelector.h"
#include "MainMenuSelector.generated.h"

class UBaseMenuButton;
/**
 * 
 */
UCLASS()
class COMMONUISETUP_API UMainMenuSelector : public UBaseMenuSelector
{
	GENERATED_UCLASS_BODY()
public: 
	UMainMenuSelector(); 
	
	UBaseMenuButton* GetNewGameButton() const {return WB_NewGame; }
	
	UBaseMenuButton* GetSettingsButton() const {return WB_Settings; };
	
	UBaseMenuButton* GetQuitButton() const {return WB_Quit; }

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
private: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_NewGame;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Settings;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Quit;
};
