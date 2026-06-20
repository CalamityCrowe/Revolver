// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseCommonActivatableWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class COMMONUISETUP_API UHUDWidget : public UBaseCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
public: 
	
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
};
