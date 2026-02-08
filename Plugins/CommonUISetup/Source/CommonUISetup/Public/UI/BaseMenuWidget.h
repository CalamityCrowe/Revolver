// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseMenuWidget.generated.h"

class UCommonActivatableWidgetSwitcher; 

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UBaseMenuWidget : public UCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
public: 

	virtual void NativeOnActivated() override;
	
protected: 
	 
	virtual void ChangeWidgetPanel(UCommonActivatableWidgetSwitcher* Switcher, UWidget* InWidget);

    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
private: 
	
};
