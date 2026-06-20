// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuFiles/CreditsStructure.h"
#include "CreditCategory.generated.h"

class UCreditRole;
class UCommonTextBlock;
class UVerticalBox;
/**
 * 
 */
UCLASS(Abstract)
class COMMONUISETUP_API UCreditCategory : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	
	void InitializeCategory(const FText& InText); 
	
	void AddCredit(const FCredits& Credit);
	
protected: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VB_Credit;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_CreditCategory;
	
	UPROPERTY(EditDefaultsOnly, Category= "CommonUI|Credits")
	TSubclassOf<UCreditRole> CreditRoleWidgetClass;
	

private: 
	UPROPERTY()
	TMap<FString, UCreditRole*> Roles; 
};
