// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuWidget.h"
#include "PauseMenuWidget.generated.h"


class UPauseMenuSelector;
/**
 * 
 */
UCLASS(Abstract,  HideDropdown)
class COMMONUISETUP_API UPauseMenuWidget : public UBaseMenuWidget
{
	GENERATED_UCLASS_BODY()
public: 
	virtual void NativeConstruct() override; 
protected: 
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UPauseMenuSelector> WM_PauseSelector;
	
	
	UFUNCTION()
	virtual void OnResumeGamePressed(); 
	UFUNCTION()
	virtual void OnMainMenuPressed(); 
	
	
	virtual void BackToMainMenuPressed() override;
	
	virtual bool AllPagesSet() const override{return (WM_PauseSelector && Super::AllPagesSet());};
};
