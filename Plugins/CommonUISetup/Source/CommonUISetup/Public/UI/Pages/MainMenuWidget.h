// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Pages/BaseMenuWidget.h"
#include "MainMenuWidget.generated.h"

class UOptionsPanel;
class UConfirmationDialogueWidget;
class UMainMenuSelector;
class USettingsMenuSelector;
class UBaseMenuButton;
class UVerticalBox; 

/**
 * 
 */
UCLASS()
class COMMONUISETUP_API UMainMenuWidget : public UBaseMenuWidget
{
	GENERATED_UCLASS_BODY()
public: 

	
	virtual void NativeConstruct() override;

	
	
private: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetSwitcher> WS_MainMenu; 
	
	//TODO: Implement the actual widgets correctly in the blueprints and assign them in there
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMainMenuSelector> WM_MainMenu; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USettingsMenuSelector> WM_Settings;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptionsPanel> WM_AudioOptions;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptionsPanel> WM_VideoOptions;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOptionsPanel> WM_DisplayOptions;
	

	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "Quit Widget")
	TSubclassOf<UConfirmationDialogueWidget> QuitWidgetClass; 
	
	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "Quit Widget")
	FText QuitMessage; 
	
private: 
	
	UFUNCTION()
	void OnSettingsPressed();
	
	UFUNCTION()
	void OnQuitPressed();
	
	UFUNCTION()
	void OnAudioOptionsPressed();
	UFUNCTION()
	void OnVideoOptionsPressed();
	
	UFUNCTION()
	void OnControlsOptionsPressed();
	
	UFUNCTION()
	void BackToMainMenuPressed();
	
	UFUNCTION()
	void BackToSettingsPressed();
	
	UFUNCTION()
	void QuitConfirmation(bool Confirm);

	
private: 
	
	bool AllPagesSet()const {return (WM_MainMenu && WM_Settings && WM_AudioOptions && WM_VideoOptions && WM_DisplayOptions);}
};
