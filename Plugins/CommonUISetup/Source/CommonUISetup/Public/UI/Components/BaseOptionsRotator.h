// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "BaseOptionsRotator.generated.h"

class UImage; 
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UBaseOptionsRotator : public UCommonRotator
{
	GENERATED_UCLASS_BODY()
	
public: 
	void MarkAsCustom();
	
protected: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> Highlighted_Option; 
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleOptionsPopulated(int32 Count) ; 
	
	UFUNCTION(BlueprintCallable)
	virtual void HandleOptionSelected(int32 Index) ;
};
