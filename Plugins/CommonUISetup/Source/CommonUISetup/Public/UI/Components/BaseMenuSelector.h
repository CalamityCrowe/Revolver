// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MenuDelegates.h"
#include "BaseMenuSelector.generated.h"


class UVerticalBox;
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UBaseMenuSelector : public UCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
protected: 
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess), BlueprintReadWrite)
	TObjectPtr<UVerticalBox> MenuSelector; 
	
	
};
