// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BasePauseHUD.generated.h"

class UCommonActivatableWidget;
class UPauseMenuWidget;
class UBaseLayout; 

/**
 *  for this we will be doing a bity of setup outside of the HUD class to handle the pausing of the game
 *  this will be handled in the main source folders controller specifically, so we can get the correct pause function that we want for the when the game is running 
 */
UCLASS(Abstract, meta = (HideFromSelection = true))
class COMMONUISETUP_API ABasePauseHUD : public AHUD
{
	GENERATED_BODY()
public: 
	ABasePauseHUD(); 
	
	virtual void BeginPlay() override; 
	
	virtual void ShowPauseMenu(); 
	
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "CommonUI")
	TSubclassOf<UCommonActivatableWidget> PauseMenuWidgetClass; 
	
	UPROPERTY(EditDefaultsOnly, Category = "CommonUI")
	TSubclassOf<UBaseLayout> BaseLayoutClass;
	
	UPROPERTY()
	UPauseMenuWidget* PauseMenuWidget;
	
	UPROPERTY()
	UBaseLayout* BaseLayout;
	
	
	
};
