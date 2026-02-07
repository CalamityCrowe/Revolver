// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuFIles/BaseMenuHUD.h"

#include "UI/BaseMenuWidget.h"

ABaseMenuHUD::ABaseMenuHUD()
{
}

void ABaseMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UBaseMenuWidget>(GetWorld(), MenuWidgetClass);
		MenuWidget->AddToViewport(); 
		
		if (APlayerController* PC = GetOwningPlayerController())
		{
			FInputModeUIOnly InputMode; 
			InputMode.SetWidgetToFocus(MenuWidget->TakeWidget()); 
			PC->SetInputMode(InputMode);
		} 
	}
}
