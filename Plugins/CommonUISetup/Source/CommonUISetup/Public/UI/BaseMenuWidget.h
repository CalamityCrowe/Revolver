// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseMenuWidget.generated.h"

class UCommonActivatableWidgetSwitcher; 

/**
 * 
 */
UCLASS(meta = (HideFromSelection = true))
class COMMONUISETUP_API UBaseMenuWidget : public UCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UBaseMenuWidget(); 

protected: 
	 
	virtual void ChangeWidgetPanel(UCommonActivatableWidgetSwitcher* Switcher, UWidget* InWidget);

	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override; 
private: 
	
};
