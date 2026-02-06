// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseMenuWidget.h"
#include "MainMenuWidget.generated.h"

class UConfirmationDialogueWidget;
class UBaseMenuSelector;
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
	UMainMenuWidget();
	
	virtual void NativeConstruct() override;

	
private: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetSwitcher> WS_MainMenu; 
	
	//TODO: Implement the actual widgets correctly in the blueprints and assign them in there
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuSelector> WM_MainMenu; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuSelector> WM_Settings;


	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "Quit Widget")
	TSubclassOf<UConfirmationDialogueWidget> QuitWidgetClass; 
	
	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "Quit Widget")
	FText QuitMessage; 
	
private: 
	
	void OnSettingsPressed();
	
	void OnQuitPressed();
	
	UFUNCTION()
	void QuitConfirmation(bool Confirm);
	
};
