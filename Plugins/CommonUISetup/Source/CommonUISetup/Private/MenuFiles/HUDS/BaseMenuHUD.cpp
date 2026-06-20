// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuFIles/HUDS/BaseMenuHUD.h"

#include "UI/BaseLayout.h"

ABaseMenuHUD::ABaseMenuHUD()
{
}

void ABaseMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (BaseLayoutClass)
	{
		BaseLayout = CreateWidget<UBaseLayout>(PlayerOwner, BaseLayoutClass);
		BaseLayout->AddToViewport(); 
		
		BaseLayout->PushWidget(MenuWidgetClass); 
	}
}

UCommonActivatableWidget* ABaseMenuHUD::PushWidget_Implementation(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if(BaseLayout)
	{
		return BaseLayout->PushWidget(WidgetClass); 
	}
	return nullptr;
}
