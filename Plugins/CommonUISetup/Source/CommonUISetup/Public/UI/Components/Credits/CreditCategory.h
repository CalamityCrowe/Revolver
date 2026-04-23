// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditCategory.generated.h"

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
	
protected: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "CommonUI|Credits", meta = (BindWidget))
	TObjectPtr<UVerticalBox> VB_Credit;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "CommonUI|Credits", meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_CreditCategory;
};
