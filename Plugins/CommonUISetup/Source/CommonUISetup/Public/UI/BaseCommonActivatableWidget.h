// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseCommonActivatableWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UBaseCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
public: 
	
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override; 
};
