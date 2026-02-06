// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseMenuHUD.generated.h"

class UBaseMenuWidget; 

/**
 * 
 */
UCLASS(Abstract, meta = (HideFromSelection = true))
class COMMONUISETUP_API ABaseMenuHUD : public AHUD
{
	GENERATED_BODY()
public: 
	
	ABaseMenuHUD(); 
	
	virtual void BeginPlay() override;
	
private: 
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBaseMenuWidget> MenuWidgetClass;
	
	UBaseMenuWidget* MenuWidget;
};
