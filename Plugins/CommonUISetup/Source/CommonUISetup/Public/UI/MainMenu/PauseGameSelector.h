// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/BaseMenuSelector.h"
#include "PauseGameSelector.generated.h"

class UBaseMenuButton;
/**
 * 
 */
UCLASS(Abstract, Hidedropdown)
class COMMONUISETUP_API UPauseGameSelector : public UBaseMenuSelector
{
	GENERATED_UCLASS_BODY()
public: 
	FOnButtonPressed OnResumePressed;
	FOnButtonPressed OnSettingsPressed;
	FOnButtonPressed OnMainMenuPressed;
	
	virtual void NativeConstruct() override;
	
private: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_ResumeGame; 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Settings;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_MainMenu;
	
	void OnResumeGameButtonPressed() const; 
	void OnSettingsButtonPressed() const;
	void OnMainMenuButtonPressed() const;
};
