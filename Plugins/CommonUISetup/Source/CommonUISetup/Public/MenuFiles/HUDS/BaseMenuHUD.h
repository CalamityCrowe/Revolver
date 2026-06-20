// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interfaces/HUDInterface.h"
#include "BaseMenuHUD.generated.h"

class UCommonActivatableWidget;
class UBaseLayout;
class UBaseMenuWidget; 
class UCommonActivatableWidgetStack;
/**
 * 
 */
UCLASS(Abstract, meta = (HideFromSelection = true))
class COMMONUISETUP_API ABaseMenuHUD : public AHUD,public IHUDInterface
{
	GENERATED_BODY()
public: 
	
	ABaseMenuHUD(); 
	
	virtual void BeginPlay() override;

	virtual UCommonActivatableWidget* PushWidget_Implementation(TSubclassOf<UCommonActivatableWidget> WidgetClass) override;
	
private: 
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UCommonActivatableWidget> MenuWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBaseLayout> BaseLayoutClass;
	
	UCommonActivatableWidgetStack* MenuStack; 
	
	UPROPERTY()
	UBaseMenuWidget* MenuWidget;
	UPROPERTY()
	UBaseLayout* BaseLayout;
};
