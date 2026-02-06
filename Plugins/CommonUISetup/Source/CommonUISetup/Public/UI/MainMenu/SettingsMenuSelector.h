// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Components/BaseMenuSelector.h"
#include "SettingsMenuSelector.generated.h"

class UBaseMenuButton; 

/**
 * 
 */
UCLASS()
class COMMONUISETUP_API USettingsMenuSelector : public UBaseMenuSelector
{
	GENERATED_UCLASS_BODY()
	
public: 
	USettingsMenuSelector(); 
	
	UBaseMenuButton* GetAudioButton() const {return WB_Audio;}
	UBaseMenuButton* GetVideoButton() const {return WB_Video;}
	UBaseMenuButton* GetControlsButton() const {return WB_Controls;}
	UBaseMenuButton* GetBackButton() const {return WB_Back;}
	
private: 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Audio;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Video;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Controls;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_Back;
	
};
