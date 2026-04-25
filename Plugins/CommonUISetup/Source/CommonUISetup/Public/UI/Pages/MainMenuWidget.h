// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Pages/BaseMenuWidget.h"
#include "MainMenuWidget.generated.h"

class UCreditsWidget;
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

	
	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "CommonUI")
	TSubclassOf<UConfirmationDialogueWidget> QuitWidgetClass; 
	
	UPROPERTY(EditDefaultsOnly,meta = (AllowPrivateAccess), Category = "CommonUI")
	FText QuitMessage; 
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> ShowCreditsAnim; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCreditsWidget> WM_Credits; 
	
	
protected: 
	
	UFUNCTION()
	void OnNewGamePressed(); 
	UFUNCTION()
	void OnCreditsPressed();
	UFUNCTION()
	void CreditsFinished(); 
	
	UFUNCTION()
	void OnQuitPressed();
	
	
	virtual void BackToMainMenuPressed() override;
	
	UFUNCTION()
	void QuitConfirmation(bool Confirm);

	
	
	virtual bool AllPagesSet()const override {return (WM_MainMenu && Super::AllPagesSet());}
};
