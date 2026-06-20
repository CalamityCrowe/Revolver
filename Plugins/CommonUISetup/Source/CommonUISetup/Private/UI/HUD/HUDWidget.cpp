// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HUDWidget.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
}

TOptional<FUIInputConfig> UHUDWidget::GetDesiredInputConfig() const
{
	FUIInputConfig config = FUIInputConfig
	(ECommonInputMode::Game,
		EMouseCaptureMode::CapturePermanently,
		EMouseLockMode::LockAlways,true);
	config.bIgnoreLookInput = false;
	config.bIgnoreMoveInput = false;
	return config;
}
