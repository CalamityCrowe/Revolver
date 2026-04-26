// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseCommonActivatableWidget.h"
#include "CreditsWidget.generated.h"

class UBaseMenuButton;
DECLARE_DYNAMIC_DELEGATE(FOnCreditsFinished); 

/**
 * 
 */

class UCreditCategory;
class UScrollBox;
class UOverlay; 

UCLASS(Abstract)
class COMMONUISETUP_API UCreditsWidget : public UBaseCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
public: 
	virtual void NativePreConstruct() override; 
	virtual void NativeConstruct() override; 
	
	FOnCreditsFinished OnCreditsFinished;
	
	void RollCredits(); 
	
protected: 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> Overlay; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> SCB_Credits;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseMenuButton> WB_BackButton; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits")
	TObjectPtr<UDataTable> CreditsTable;
	

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits")
	TSubclassOf<UCreditCategory> CreditCategoryWidgetClass; 	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits")
	FVector2D SpacerSize; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits")
	float ScrollSpeed; 
	
	
	UFUNCTION()
	void OnBackButtonPressed();
	
	void ResetCredits();
private: 
	
	void InitializeCredits(); 
	
	void AddSpacer(); 
	
	
	void ScrollCredits(); 
	
	UPROPERTY()
	TMap<FString, UCreditCategory*> CreditCategories;
	
	FTimerHandle ScrollTimerHandle; 
	
	bool bScrolling = true;
};
