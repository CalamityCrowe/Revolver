// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/CommonBoundActionButton.h"
#include "BaseMenuButton.generated.h"

class UOverlay; 

/**
 * 
 */
UCLASS(Abstract)
class COMMONUISETUP_API UBaseMenuButton : public UCommonBoundActionButton
{
	GENERATED_UCLASS_BODY()
public:
	UBaseMenuButton(); 
	
	virtual void NativePreConstruct() override;	
	
	
private: 
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> ButtonOverlay;
	
	UPROPERTY(EditAnywhere,Category = "Button",meta = (BindWidget, AllowPrivateAccess))
	FText ButtonText;
};
