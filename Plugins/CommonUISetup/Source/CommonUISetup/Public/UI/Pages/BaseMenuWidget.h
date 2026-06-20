// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseCommonActivatableWidget.h"
#include "BaseMenuWidget.generated.h"

class UOptionsPanel;
class USettingsMenuSelector;
class UCommonActivatableWidgetSwitcher; 

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UBaseMenuWidget : public UBaseCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
public: 

	virtual void NativeOnActivated() override;
	
	virtual void NativeConstruct() override;
	
protected: 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetSwitcher> WS_MainMenu; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USettingsMenuSelector> WM_Settings;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptionsPanel> WM_AudioOptions;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptionsPanel> WM_VideoOptions;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptionsPanel> WM_DisplayOptions;
	
	
	virtual void ChangeWidgetPanel(UCommonActivatableWidgetSwitcher* Switcher, UWidget* InWidget);


	UFUNCTION()
	virtual void OnSettingsPressed();
	
	UFUNCTION()
	virtual void OnAudioOptionsPressed();
	UFUNCTION()
	virtual void OnVideoOptionsPressed();
	
	UFUNCTION()
	virtual void OnDisplayOptionsPressed();
	
	UFUNCTION()
	virtual void BackToMainMenuPressed(){};
	
	UFUNCTION()
	virtual void BackToSettingsPressed();
	
	
	virtual bool AllPagesSet() const{return (WM_Settings && WM_AudioOptions && WM_VideoOptions && WM_DisplayOptions); }
private: 
	
};
