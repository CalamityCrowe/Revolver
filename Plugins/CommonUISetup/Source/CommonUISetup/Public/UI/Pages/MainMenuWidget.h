// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Pages/BaseMenuWidget.h"
#include "MainMenuWidget.generated.h"

class UConfirmationDialogueWidget;
class UMainMenuSelector;
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
	
	//TODO: Implement the actual widgets correctly in the blueprints and assign them in there
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMainMenuSelector> WM_MainMenu; 
	
	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "Quit Widget")
	TSubclassOf<UConfirmationDialogueWidget> QuitWidgetClass; 
	
	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "Quit Widget")
	FText QuitMessage; 
	
protected: 
	
	UFUNCTION()
	void OnNewGamePressed(); 
	
	UFUNCTION()
	void OnQuitPressed();
	
	
	virtual void BackToMainMenuPressed() override;
	
	UFUNCTION()
	void QuitConfirmation(bool Confirm);

	
	
	virtual bool AllPagesSet()const override {return (WM_MainMenu && Super::AllPagesSet());}
};
