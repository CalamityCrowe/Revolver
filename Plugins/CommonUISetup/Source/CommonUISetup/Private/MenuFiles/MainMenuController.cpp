// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuFiles/MainMenuController.h"

AMainMenuController::AMainMenuController()
{
	
}

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly()); 
}
