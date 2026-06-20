// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseCommonActivatableWidget.h"

UBaseCommonActivatableWidget::UBaseCommonActivatableWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

TOptional<FUIInputConfig> UBaseCommonActivatableWidget::GetDesiredInputConfig() const
{
	FUIInputConfig config = FUIInputConfig(ECommonInputMode::Menu,EMouseCaptureMode::CapturePermanently,false);
	config.bIgnoreLookInput = true;
	config.bIgnoreMoveInput = true;
	return config;
}
