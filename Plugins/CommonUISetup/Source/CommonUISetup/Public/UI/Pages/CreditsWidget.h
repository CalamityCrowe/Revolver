// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseCommonActivatableWidget.h"
#include "CreditsWidget.generated.h"

/**
 * 
 */

class UScrollBox;
class UOverlay; 

UCLASS(Abstract)
class COMMONUISETUP_API UCreditsWidget : public UBaseCommonActivatableWidget
{
	GENERATED_UCLASS_BODY()
public: 
	 
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits", meta = (BindWidget))
	TObjectPtr<UOverlay> Overlay; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CommonUI|Credits", meta = (BindWidget))
	TObjectPtr<UScrollBox> SCB_Credits;
};
