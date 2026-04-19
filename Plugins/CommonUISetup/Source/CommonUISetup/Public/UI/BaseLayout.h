// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "BaseLayout.generated.h"


class UOverlay; 
class UCommonActivatableWidgetStack; 
class UCommonActivatableWidget;
/**
 * 
 */
UCLASS(Abstract, HideDropdown)
class COMMONUISETUP_API UBaseLayout : public UCommonUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	virtual void NativePreConstruct() override;
	
	virtual void PushWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	
protected: 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UOverlay> Overlay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> CAWS_WidgetStack;
};
