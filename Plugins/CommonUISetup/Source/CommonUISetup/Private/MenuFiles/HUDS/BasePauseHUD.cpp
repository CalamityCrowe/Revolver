// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuFiles/HUDS/BasePauseHUD.h"
#include "UI/BaseLayout.h"
#include "UI/Pages/PauseMenuWidget.h"

ABasePauseHUD::ABasePauseHUD()
{
	
}

void ABasePauseHUD::BeginPlay()
{
	if (BaseLayoutClass)
	{
		BaseLayout = CreateWidget<UBaseLayout>(PlayerOwner, BaseLayoutClass);
		BaseLayout->AddToViewport(); 
		
		BaseLayout->PushWidget(HUDWidgetClass); 
	}
}

void ABasePauseHUD::ShowPauseMenu()
{
	if (BaseLayout && !PauseMenuWidget)
	{
		PauseMenuWidget = BaseLayout->PushWidget(PauseMenuWidgetClass); 
	}
}

void ABasePauseHUD::RemovePauseMenu()
{
	if (PauseMenuWidget)
	{
		BaseLayout->PopWidget(*PauseMenuWidget); 
		PauseMenuWidget = nullptr;
	}
}
