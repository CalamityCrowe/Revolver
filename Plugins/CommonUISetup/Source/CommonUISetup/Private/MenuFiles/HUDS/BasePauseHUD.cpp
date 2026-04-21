// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuFiles/HUDS/BasePauseHUD.h"
#include "UI/BaseLayout.h"
ABasePauseHUD::ABasePauseHUD()
{
	
}

void ABasePauseHUD::BeginPlay()
{
	if (BaseLayoutClass)
	{
		BaseLayout = CreateWidget<UBaseLayout>(PlayerOwner, BaseLayoutClass);
		BaseLayout->AddToViewport(); 
	}
}

void ABasePauseHUD::ShowPauseMenu()
{
	if (BaseLayout)
	{
		BaseLayout->PushWidget(PauseMenuWidgetClass); 
	}
}
