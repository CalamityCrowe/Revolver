// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseCommonActivatableWidget.h"
#include "CreditsWidget.generated.h"

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
	 
	virtual void NativeOnActivated() override;
	
	
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits", meta = (BindWidget))
	TObjectPtr<UOverlay> Overlay; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits", meta = (BindWidget))
	TObjectPtr<UScrollBox> SCB_Credits;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits")
	TObjectPtr<UDataTable> CreditsTable;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits")
	TSubclassOf<UCreditCategory> CreditCategoryWidgetClass; 	
	
	
private: 
	
	void InitializeCredits(); 
	
	UPROPERTY()
	TMap<FString, UCreditCategory*> CreditCategories;
	
};
