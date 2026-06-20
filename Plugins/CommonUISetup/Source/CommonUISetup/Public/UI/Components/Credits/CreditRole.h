// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditRole.generated.h"


struct FCredits;
class UCommonTextBlock;
class UHorizontalBox; 
/**
 * 
 */
UCLASS(Abstract)
class COMMONUISETUP_API UCreditRole : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	 
	void SetRoleText(const FText& InRole); 
	
	void AddRole(const FCredits& InCredits); 
	
protected: 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HB_RoleLayout; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_Role; 
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> CT_Names;
	
};
