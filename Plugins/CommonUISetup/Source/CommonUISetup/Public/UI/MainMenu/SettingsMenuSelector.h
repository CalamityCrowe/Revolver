// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/BaseMenuSelector.h"
#include "SettingsMenuSelector.generated.h"

class UBaseMenuButton; 

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API USettingsMenuSelector : public UBaseMenuSelector
{
	GENERATED_UCLASS_BODY()
	
public: 
	USettingsMenuSelector(); 
	
	FOnButtonPressed OnAudioPressed;
	FOnButtonPressed OnVideoPressed;
	FOnButtonPressed OnControlsPressed;
	FOnButtonPressed OnBackPressed;
	
	virtual void NativeConstruct() override;
	
	
private: 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Audio;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Video;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Controls;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Back;
	
	
	void OnAudioButtonPressed(); 
	void OnVideoButtonPressed();
	void OnControlsButtonPressed();
	void OnBackButtonPressed();
};
